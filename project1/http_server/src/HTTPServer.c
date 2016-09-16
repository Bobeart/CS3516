// William Hartman
// CS3516 Project 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include "ServerSocketWrapper.h"

//Global declartions of socket file descriptors so we can close them on SIGINT
int sockfd;
int connfd;

int main(int argc, char** argv) {
  //Catch SIGINT (adapted from: http://beej.us/guide/bgipc/output/html/multipage/signals.html)
  void sigint_handler(int sig); /* prototype */
  struct sigaction sa;
  sa.sa_handler = sigint_handler;
  sa.sa_flags = 0; // or SA_RESTART
  sigemptyset(&sa.sa_mask);
  if (sigaction(SIGINT, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  //Check arguments
  if(argc != 2) {
    printf("Improper usage!\n");
    printf("./http_server port_number\n");
    return -1;
  }

  char* port_number = argv[1];

  //Build and hold onto our main socket
  struct addrinfo* servinfo = buildAddrInfo(port_number);
  sockfd = startUpSocket(servinfo);

  //Main server loop
  while(1) {
    //Wait to accept a connection
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    connfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    if(connfd < 0) {
      printf("Could not accept!\n");
    }

    //Pull in a request with recv, print it
    char* received_request = receiveFrom(connfd);
    printf("Received request:\n%s\n\n", received_request);

    //Parse the url for the requested file.
    strtok(received_request, " "); //Split on space
    char* url = strtok(NULL, " ");
    //Want to start path after the third '/' (due to http://abc.xyz/)
    char* file_path = &strrchr(strrchr(strrchr(url, '/'), '/'), '/')[1];

    //Open the file. Send it if found, 404 if not found.
    int filefd = open(file_path, O_RDONLY, S_IREAD | S_IWRITE);
    if(filefd < 0) {
      printf("Requested file \"%s\" was not found!\n", file_path);
      send404(connfd);
    } else {
      printf("Found file \"%s\", sending...\n", file_path);
      sendFile(connfd, filefd, file_path);
    }

    //Close the connection, free stuff, so we can loop safely
    free(received_request);
    close(connfd);
  }
  return 0;
}

//Handle Control+C, close any open sockets
void sigint_handler(int sig)
{
    printf("\nExiting server\n");
    close(sockfd);
    close(connfd);
    exit(0);
}

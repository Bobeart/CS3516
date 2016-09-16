// William Hartman
// CS3516 Project 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/stat.h>
#include <fcntl.h>

#include "ServerSocketWrapper.h"

int main(int argc, char** argv) {

  //Check arguments
  if(argc != 2) {
    printf("Improper usage!\n");
    printf("./http_server port_number\n");
    return -1;
  }

  char* port_number = argv[1];

  struct addrinfo* servinfo = buildAddrInfo(port_number);
  int sockfd = startUpSocket(servinfo);

  while(1) {
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    int newfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    if(newfd < 0) {
      printf("Could not accept!\n");
    }

    char* received_request = receiveFrom(newfd);
    printf("Received request:\n%s\n\n", received_request);

    strtok(received_request, " "); //Split on space
    char* url = strtok(NULL, " ");
    char* file_path = url;
    int filefd = open(&strrchr(file_path, '/')[1], O_RDONLY, S_IREAD | S_IWRITE);

    if(filefd < 0) {
      printf("Requested file \"%s\" was not found!\n", file_path);
      send404(newfd);
    } else {
      printf("Found file \"%s\", sending...\n", file_path);
      sendFile(newfd, filefd);
    }

    close(newfd);
  }
  return 0;
}

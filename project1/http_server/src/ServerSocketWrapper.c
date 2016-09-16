// William Hartman
// CS3516 Project 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "ServerSocketWrapper.h"

#define SOCKET_BACKLOG 5

// A more convenient way to get an addrinfo struct out of a Port number
struct addrinfo* buildAddrInfo(char* port) {
  struct addrinfo hints;
  struct addrinfo *servinfo;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if (getaddrinfo(NULL, port, &hints, &servinfo) != 0) {
    printf("getaddrinsfo failed!\n");
    exit(1);
  }

  return servinfo;
}

// A convenient way to build a socket, bind it, and start listening
int startUpSocket(struct addrinfo* servinfo) {
  //Make a socket
  int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (sockfd < 0) {
    printf("Could not open a socket!\n");
    exit(1);
  }

  //Bind to the socket
  int bind_status = bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
  if(bind_status < 0) {
    printf("Could not bind socket!\n");
    exit(1);
  }

  //Listen
  int listen_status = listen(sockfd, SOCKET_BACKLOG);
  if(listen_status < 0) {
    printf("Could not listen to socket!\n");
    exit(1);
  }

  return sockfd;
}

void sendFile(int sockfd, char* file_name) {

}

void send404(int sockfd) {
  //send HTTP error message header
  char buf[256];
  strcpy(buf, "HTTP/1.1 404 Not Found\r\nContent-Type:text/html\r\n\n");
  send(sockfd, buf, strlen(buf), 0);

  //send HTTP error message body
  strcpy(buf, "<html><body><h1>404! Can't find file!</h1></body></html>");
  send(sockfd, buf, strlen(buf), 0);
}

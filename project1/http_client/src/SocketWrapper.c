// William Hartman
// CS3516 Project 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "SocketWrapper.h"

#define RECV_BUF_SIZE 1024
#define USER_AGENT_STR "Mozilla/5.0 (X11; Linux x86_64; rv:48.0) Gecko/20100101 Firefox/48.0"

// A more convenient way to get an addrinfo struct out of a URL/Port number
struct addrinfo* buildAddrInfo(char* url, char* port) {
  struct addrinfo hints;
  struct addrinfo *servinfo;
  memset(&hints, 0, sizeof hints);
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  char* host_name = makeHostFromURL(url);
  if (getaddrinfo(host_name, port, &hints, &servinfo) != 0) {
    printf("getaddrinsfo failed! errno: %d\n", errno);
    exit(1);
  }
  free(host_name);

  return servinfo;
}

// A quick and dirty way of finding the host name from a complete URL.
// This just takes the part before the first slash as the host name.
// This means the urls with 'http://' don't work.
char* makeHostFromURL(char* url) {
  int host_name_len = strcspn(url, "/");
  char* host_name = malloc(host_name_len);
  strncpy(host_name, url, host_name_len);

  return host_name;
}

// A convenient way to build a socket and connect to it.
// Return value is the socket file descriptor
int makeAndConnectToSocket(struct addrinfo* servinfo) {
  //Make a socket
  int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (sockfd < 0) {
    printf("Could not open a socket! errno: %d\n", errno);
    exit(1);
  }

  //Connect the socket
  int conn_status = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
  if (conn_status < 0){
    printf("Could not connect to the server! errno: %d\n", errno);
    exit(1);
  }

  return sockfd;
}

// Make a request to the given url to the socket. All output is printed
void printRequestResponse(int sockfd, char* url) {
  //Build a request
  char* host_name = makeHostFromURL(url);
  char* req = buildGETRequest(url, host_name);
  free(host_name);

  //Send the request to the server
  printf("----- REQUESTING -----\n%s\n", req);
  int send_res = send(sockfd, req, strlen(req), 0);
  if(send_res < 0) {
    printf("Error in send! errno: %d\n", errno);
    exit(1);
  }

  //Read from server into the buffer. Keep reading until
  //the server closes the connection.
  char buf[RECV_BUF_SIZE];
  printf("----- FROM SERVER -----\n");
  int recv_res = 0;
  do {
    //receive and output what we can fit
    recv_res = recv(sockfd, buf, RECV_BUF_SIZE, 0);

    //Print the result (extra stuff to not print garbage memory locs)
    char printable_res[RECV_BUF_SIZE];
    strncpy(printable_res, buf, recv_res);
    printf("%s", printable_res);

    //Zero out buffer to ready it for the next round
    memset(buf, 0, sizeof(buf));

    //Exit on error.
    if(recv_res < 0) {
      printf("Error in recv! errno: %d\n", errno);
      exit(1);
    }
  } while (recv_res > 0);
  printf("\n----- END RESPONSE -----\n");
}

// Build a get request from a URL and host using a premade format string.
char* buildGETRequest(char* page, char* host) {
  char* result_str = malloc(2048);
  //Giant format string adapted from HTTP requests I looked at
  char* getBuilder = "GET http://\%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\nAccept-Language: en-us,en\r\nConnection: close\r\nCache-Control: no-cache\r\n\r\n";

  //Insert proper values into format string
  sprintf(result_str, getBuilder, page, host, USER_AGENT_STR);

  return result_str;
}

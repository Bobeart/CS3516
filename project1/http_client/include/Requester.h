// William Hartman
// CS3516 Project 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//Look to Requester.c for function descriptions and comments
void printRequestResponse(int sockfd, char* url);
char* makeHostFromURL(char* url);
struct addrinfo* buildAddrInfo(char* url, char* port);
int makeAndConnectToSocket(struct addrinfo* servinfo);
char* buildGETRequest(char* page, char* host);

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void printRequestResponse(int sockfd, char* url);
char* makeHostFromURL(char* url);
struct addrinfo* buildAddrInfo(char* url, char* port);
int makeAndConnectToSocket(struct addrinfo* servinfo);
char* buildGETRequest(char* page, char* host);

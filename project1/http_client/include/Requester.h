#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

void makeRequest(char* url, char* port);
char* buildGETRequest(char* page, char* host);
struct hostent* getHostEnt(char* url);

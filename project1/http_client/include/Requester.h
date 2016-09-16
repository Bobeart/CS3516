#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

float makeRequest(char* url, char* port, int print);
char* buildGETRequest(char* page, char* host);
float getElapsedMilliseconds(struct timeval tm1, struct timeval tm2);

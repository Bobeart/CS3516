// William Hartman
// CS3516 Project 1

//Look to SocketWrapper.c for function descriptions and comments
void printRequestResponse(int sockfd, char* url);
char* makeHostFromURL(char* url);
struct addrinfo* buildAddrInfo(char* url, char* port);
int makeAndConnectToSocket(struct addrinfo* servinfo);
char* buildGETRequest(char* page, char* host);

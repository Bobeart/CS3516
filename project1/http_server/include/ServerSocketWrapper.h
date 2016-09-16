// William Hartman
// CS3516 Project 1

struct addrinfo* buildAddrInfo(char* port);
int startUpSocket(struct addrinfo* servinfo);
void sendFile(int sockfd, char* file_name);
void send404(int sockfd);

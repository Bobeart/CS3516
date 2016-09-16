#include "Requester.h"

#define HOST_BUFFER_LEN 256
#define REQUEST_BUFFER_LEN 256
#define USER_AGENT_STR "Mozilla/5.0 (X11; Linux x86_64; rv:48.0) Gecko/20100101 Firefox/48.0"

void makeRequest(char* url, char* port) {
  //Get addrinfo struct from URL
  struct addrinfo hints;
  struct addrinfo *servinfo;
  memset(&hints, 0, sizeof hints);
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo(url, port, &hints, &servinfo) != 0) {
    printf("getaddrinfo failed!\n");
    exit(1);
  }

  //Print the IP address for the user
  char ipstr[INET6_ADDRSTRLEN];
  inet_ntop(servinfo->ai_family, servinfo->ai_addr, ipstr, sizeof ipstr);
  printf("Found IP adress %s\n", ipstr);

  //Make a socket
  int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (sockfd < 0) {
    printf("Could not open a socket!\n");
    exit(1);
  }

  //Connect the socket
  int conn_status = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
  if (conn_status < 0){
    printf("Could not connect to the server!\n");
    exit(1);
  }

  char* req = buildGETRequest("http://google.com/index.html", "google.com");
  printf("requesting %s\n", req);
  if (write(sockfd, req, sizeof(req)) <= 0) {
    printf("Error in the write call!\n");
  }

  char recieved_buffer[2048];
  while(1) {
    bzero(recieved_buffer, sizeof(recieved_buffer));

    int read = recv(sockfd, recieved_buffer, sizeof(recieved_buffer) - 2, 0);
    printf("read\n");
    if(read <= 0) {
      printf("Bailing on read! %d\n", read);
      break;
    } else {
      printf(".%s", recieved_buffer);
    }
  }

  freeaddrinfo(servinfo);
}

char* buildGETRequest(char* page, char* host) {
  char* result_str = malloc(8 * 1024);
  char* getBuilder = "GET /%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\nAccept-Language: en-us,en\r\nConnection: close\r\nCache-Control: no-cache\r\n\r\n";
  sprintf(result_str, getBuilder, page, host, USER_AGENT_STR);

  return result_str;
}
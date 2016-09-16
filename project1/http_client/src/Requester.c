#include "Requester.h"

#define RECV_BUF_SIZE 1024
#define USER_AGENT_STR "Mozilla/5.0 (X11; Linux x86_64; rv:48.0) Gecko/20100101 Firefox/48.0"

void printRequestResponse(int sockfd, char* url) {
  //Build a request
  char* host_name = makeHostFromURL(url);
  char* req = buildGETRequest(url, host_name);
  free(host_name);

  //Send the request to the server
  printf("----- REQUESTING -----\n%s\n", req);
  int send_res = send(sockfd, req, strlen(req), 0);
  if(send_res < 0) {
    printf("Error in send!\n");
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
    printf("%s", buf);

    memset(buf, 0, sizeof(buf));

    //Exit on error.
    if(recv_res < 0) {
      printf("Error in recv!\n");
      exit(1);
    }
  } while (recv_res > 0);
  printf("\n----- END RESPONSE -----\n");
}

struct addrinfo* buildAddrInfo(char* url, char* port) {
  struct addrinfo hints;
  struct addrinfo *servinfo;
  memset(&hints, 0, sizeof hints);
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  char* host_name = makeHostFromURL(url);
  if (getaddrinfo(host_name, port, &hints, &servinfo) != 0) {
    printf("getaddrinsfo failed!\n");
    exit(1);
  }
  free(host_name);

  return servinfo;
}

char* makeHostFromURL(char* url) {
  int host_name_len = strcspn(url, "/");
  char* host_name = malloc(host_name_len);
  strncpy(host_name, url, host_name_len);

  return host_name;
}

int makeAndConnectToSocket(struct addrinfo* servinfo) {
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

  return sockfd;
}

char* buildGETRequest(char* page, char* host) {
  char* result_str = malloc(8 * 1024);
  char* getBuilder = "GET http://\%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\nAccept-Language: en-us,en\r\nConnection: close\r\nCache-Control: no-cache\r\n\r\n";
  sprintf(result_str, getBuilder, page, host, USER_AGENT_STR);

  return result_str;
}

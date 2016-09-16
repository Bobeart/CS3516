#include "Requester.h"

#define RECV_BUF_SIZE 1024
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

  //Build a request and send it the server
  char* req = buildGETRequest(url, "");
  printf("requesting %s\n", req);
  int send_res = send(sockfd, req, strlen(req), 0);
  if(send_res < 0) {
    printf("Error in send!\n");
    exit(1);
  }

  char buf[RECV_BUF_SIZE];

  //Read from server into the buffer. Keep reading until
  //the server closes the connection.
  printf("----- FROM SERVER -----\n");
  int recv_res = 0;
  do {
    //receive and output what we can fit
    recv_res = recv(sockfd, buf, sizeof(buf), 0);
    printf("%s", buf);
    memset(buf, 0, sizeof(buf));

    //Exit on error.
    if(recv_res < 0) {
      printf("Error in recv!\n");
      exit(1);
    }
  } while (recv_res > 0);

  //Close everthing
  close(sockfd);
  freeaddrinfo(servinfo);
}

char* buildGETRequest(char* page, char* host) {
  char* result_str = malloc(8 * 1024);
  char* getBuilder = "GET http://\%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\nAccept-Language: en-us,en\r\nConnection: close\r\nCache-Control: no-cache\r\n\r\n";
  sprintf(result_str, getBuilder, page, host, "");

  return result_str;
}

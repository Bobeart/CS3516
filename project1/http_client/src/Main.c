#include <stdio.h>
#include <stdlib.h>

#include "Requester.h"

void onIncorrectArgs();

int main(int argc, char** argv) {
  //Exit if args are incorrect
  if(!(argc == 3 || argc == 4)) {
    onIncorrectArgs();
    return -1;
  }

  //Parse args
  int print_rtt = argc == 4;
  char* request_url = print_rtt ? argv[2] : argv[1];
  char* port_number = print_rtt ? argv[3] : argv[2];

  printf("Requesting %s on port %s\n", request_url, port_number);
  printf("Printing RTT: %s\n", print_rtt ? "true" : "false");

  //Make request
  makeRequest(request_url, port_number);

  return 0;
}

void onIncorrectArgs() {
  printf("Improper usage!\n");
  printf("./http_client [-options] server_url port_number\n");
  printf("\t[-options]:\n");
  printf("\t-p\tprints the RTT for accessing the URL on the terminal before server’s response\n");
}

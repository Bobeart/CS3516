#include <stdio.h>
#include <stdlib.h>

#include "Requester.h"

#define NUM_RTT_TRIALS 10

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

  //Make request
  if(print_rtt) {
    printf("Finding RTT over %d trials...\n", NUM_RTT_TRIALS);

    int i;
    float sum = 0;
    for(i = 0; i < NUM_RTT_TRIALS; i++) {
      int rtt = makeRequest(request_url, port_number, 0);
      sum += rtt;
    }
    float avg = sum / NUM_RTT_TRIALS;
    printf("Average RTT over %d trials: %f milliseconds\n", NUM_RTT_TRIALS, avg);
  }

  printf("\n----- REQUESTING URL \"%s\" -----\n", request_url);
  makeRequest(request_url, port_number, 1);

  return 0;
}

void onIncorrectArgs() {
  printf("Improper usage!\n");
  printf("./http_client [-options] server_url port_number\n");
  printf("\t[-options]:\n");
  printf("\t-p\tprints the RTT for accessing the URL on the terminal before server’s response\n");
}

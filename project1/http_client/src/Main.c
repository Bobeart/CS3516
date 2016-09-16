#include "Main.h"

int main(int argc, char** argv) {
  //Exit if args are incorrect
  if(!(argc == 3 || argc == 4)) {
    printf("Improper usage!\n");
    printf("./http_client [-options] server_url port_number\n");
    printf("\t[-options]:\n");
    printf("\t-p\tprints the RTT for accessing the URL on the terminal before server’s response\n");
    return -1;
  }

  //Parse args
  int print_rtt = argc == 4;
  char* request_url = print_rtt ? argv[2] : argv[1];
  char* port_number = print_rtt ? argv[3] : argv[2];

  //Print rtt results if -p was passed
  if(print_rtt) {
    doRTTTrials(request_url, port_number, 10);
  }

  //Make a request and print the result
  struct addrinfo* servinfo = buildAddrInfo(request_url, port_number);
  int sockfd = makeAndConnectToSocket(servinfo);
  printRequestResponse(sockfd, request_url);
  close(sockfd);
  freeaddrinfo(servinfo);

  return 0;
}

// Convenience method to find an average rtt
void doRTTTrials(char* url, char* port, int num_trials) {
  printf("Finding RTT over %d trials...\n", num_trials);

  struct addrinfo* servinfo = buildAddrInfo(url, port);
  int i;
  float sum = 0;
  for(i = 0; i < num_trials; i++) {

    struct timeval start_time;
    struct timeval end_time;

    gettimeofday(&start_time, NULL);
    int sockfd = makeAndConnectToSocket(servinfo);
    gettimeofday(&end_time, NULL);
    close(sockfd);

    sum += getElapsedMilliseconds(start_time, end_time);
  }
  float avg = sum / num_trials;
  printf("Average RTT over %d trials: %f milliseconds\n", num_trials, avg);

  freeaddrinfo(servinfo);
}

// Convenience function to find the difference in milliseconds between
// two timeval structs
float getElapsedMilliseconds(struct timeval tm1, struct timeval tm2) {
  long elapsed_seconds = tm2.tv_sec - tm1.tv_sec;
  long elapsed_useconds = tm2.tv_usec - tm1.tv_usec;

  float elapsed_secs_as_msec = elapsed_seconds * 1000;
  float elapsed_usecs_as_msec = elapsed_useconds / 1000;

  return elapsed_secs_as_msec + elapsed_usecs_as_msec;
}

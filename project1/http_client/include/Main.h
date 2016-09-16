#include <stdio.h>
#include <stdlib.h>
#include "Requester.h"

void doRTTTrials(char* url, char* port, int num_trials);
float getElapsedMilliseconds(struct timeval tm1, struct timeval tm2);

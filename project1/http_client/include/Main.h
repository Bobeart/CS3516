// William Hartman
// CS3516 Project 1

#include <stdio.h>
#include <stdlib.h>
#include "Requester.h"

//Look to Main.c for function descriptions and comments
void doRTTTrials(char* url, char* port, int num_trials);
float getElapsedMilliseconds(struct timeval tm1, struct timeval tm2);

#ifndef TRAFFIC_SHAPER_RESOURCE_H
#define TRAFFIC_SHAPER_RESOURCE_H


#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <queue>
#include <sys/time.h>

typedef struct{
	int requestRate;
	int noResourceRequired;
	int bufferLength;
	int resourceRate;
	int executionTime;
} taskData;

#endif
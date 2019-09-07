#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <queue>
#include <sys/time.h>

#include "timeCalculator.h"

double time_diff(struct timeval x , struct timeval y)
{
	double x_ms , y_ms , diff;
	
	x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
	y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
	
	diff = (double)y_ms - (double)x_ms;
	
	return diff/1000.0;
}
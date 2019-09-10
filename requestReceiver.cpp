#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <queue>
#include <sys/time.h>

#include "trafficShaperResources.h"
#include "requestReceiver.h"
#include "timeCalculator.h"

using namespace std;

// Mutex for Q1
extern pthread_mutex_t lockQ1;

extern int requestNo;

extern FILE *filePointer;

extern queue<int> q1;

extern struct timeval t1;

extern pthread_t requestThread;

void* requestFun(void* data){

	//Get the request rate
	int requestRate = (*((taskData* )data)).requestRate;
		
	//Get Number of Tokens required
	int noResourceRequired = (*((taskData* )data)).noResourceRequired;
		
    while(1){
		// Wait for the request
		sleep(requestRate);
		
		printf("r%d arrives, need %d tokens\n", ++requestNo, noResourceRequired);
		fprintf(filePointer, "r%d arrives, need %d tokens\n", requestNo, noResourceRequired);
		
		// Lock the mutex for Q1
    	pthread_mutex_lock(&lockQ1);
		
		// Push the request into Q1
		q1.push(requestNo);
		
		gettimeofday(&t1, NULL);
		
		// Unlock the mutex
        pthread_mutex_unlock(&lockQ1);
		
		printf("r%d enters Q1\n", requestNo);
		fprintf(filePointer, "r%d enters Q1\n", requestNo);
		
		pthread_cancel(requestThread);
    }
}

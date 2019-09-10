#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <queue>
#include <sys/time.h>


#include "trafficShaperResources.h"
#include "timeCalculator.h"

using namespace std;

// Mutex for Q1
extern pthread_mutex_t lockQ1;

// Mutex for Q2
extern pthread_mutex_t lockQ2;

extern pthread_t tokenThread;

extern pthread_cond_t cond;

extern queue<int> q1,q2;

extern double time_spend;

extern FILE *filePointer;

extern struct timeval t1, t2;

extern int tokenNo;

void* tokenFun(void* data){

	// Get the rate for incoming resources
	int resourceRate = (*((taskData* )data)).resourceRate;
	
	//Get Number of Tokens required
	int noResourceRequired = (*((taskData* )data)).noResourceRequired; 
	
	while(1){
   		sleep(resourceRate);
        tokenNo++;
        if(tokenNo >= noResourceRequired){
            tokenNo -= noResourceRequired;
            if(!q1.empty()){
                int req = q1.front();
				gettimeofday(&t2, NULL);
				printf("r%d leaves Q1, time in Q1 = %.3fms, remaining token = %d\n", req, time_diff(t1,t2), tokenNo);
				fprintf(filePointer, "r%d leaves Q1, time in Q1 = %.3fms, remaining token = %d\n", req, time_diff(t1,t2), tokenNo);
				
				pthread_mutex_lock(&lockQ1);
				time_spend+=time_diff(t1,t2);
                q1.pop();
				gettimeofday(&t1, NULL);
				pthread_mutex_unlock(&lockQ1);
				
				printf("r%d enters Q2\n",req);
				fprintf(filePointer, "r%d enters Q2\n",req);
				pthread_mutex_lock(&lockQ2);
				q2.push(req);
				pthread_mutex_unlock(&lockQ2);
				
				pthread_cond_signal(&cond);						
			}
			
			pthread_cancel(tokenThread);			
        }
    }
}

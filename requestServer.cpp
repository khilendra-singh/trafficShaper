#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <queue>
#include <sys/time.h>

#include "trafficShaperResources.h"
#include "requestServer.h"
#include "timeCalculator.h"

using namespace std;

// Conditional variables and mutex to lock that
extern pthread_mutex_t lockCond;
extern pthread_cond_t cond;

extern queue<int> q2;

// Mutex fro Q2
extern pthread_mutex_t lockQ2;

extern struct timeval t1, t2;

extern double time_spend;

// Thread for server
extern pthread_t serverThread;

extern FILE *filePointer;

void* serverFun(void* data){

	// Extract the execution time
	int executionTime = (*((taskData* )data)).executionTime;
	
    while(1){
	
		// Wait for the requests in Q2
        pthread_cond_wait(&cond, &lockCond);
		
		// Serve till all the requests in Q2 are served
        while(!q2.empty()){
			
			//Get the next request
			int req = q2.front();
			// Lock the mutex for changing Q2
			pthread_mutex_lock(&lockQ2);
            q2.pop();
			gettimeofday(&t2, NULL);
			pthread_mutex_unlock(&lockQ2);
			printf("r%d leaves Q2, time in Q2 = %.3fms\n",req,time_diff(t1,t2));
			fprintf(filePointer, "r%d leaves Q2, time in Q2 = %.3fms\n",req,time_diff(t1,t2));
			time_spend+=time_diff(t1,t2);		
			// Reuquest Serve start
			printf("r%d begins service at S, requesting %dms of Service\n",req,executionTime*1000);
			fprintf(filePointer, "r%d begins service at S, requesting %dms of Service\n",req,executionTime*1000);
			gettimeofday(&t1, NULL);
			sleep(executionTime);
			gettimeofday(&t2, NULL);
			// Request service complete
            printf("r%d departs from S, service time = %.3fms, time in system = %.3fms\n",req,time_diff(t1,t2),time_spend+time_diff(t1,t2));
			fprintf(filePointer, "r%d departs from S, service time = %.3fms, time in system = %.3fms\n",req,time_diff(t1,t2),time_spend+time_diff(t1,t2));
			
			pthread_cancel(serverThread);
        }    
    }
}
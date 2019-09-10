#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <queue>
#include <sys/time.h>

#include "trafficShaperResources.h"
#include "requestServer.h"
#include "requestReceiver.h"
#include "tokenReceiver.h"
#include "timeCalculator.h"
#include "logger.h"

using namespace std;

// Mutex for Q1
pthread_mutex_t lockQ1 = PTHREAD_MUTEX_INITIALIZER;

// Mutex fro Q2
pthread_mutex_t lockQ2 = PTHREAD_MUTEX_INITIALIZER;

// Conditional variables and mutex to lock that
pthread_mutex_t lockCond = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


// Threads for incoming requests, resource tokens and server
pthread_t requestThread, tokenThread, serverThread;
 
double time_spend = 0.0;
 
struct timeval t1, t2;

queue<int> q1,q2;
 
int requestNo = 0, tokenNo = 0;

FILE *filePointer;
 
using namespace std;

void printError(){
	
	// Usage error
	printf("Error: Bad Comman-line Arguments\n\nUsage: trafficshaper -r r -R R -L L -x x -t t\nr : Request Rate\nR : Resource Requirement\nL : Resource Buffer Length\nx : Resource Rate\nt : Execution Time\n");
	_exit(-1);
}

int main(int argc, char** argv) {
	
	// Command-line options
	int opt;
	
	// Data related to the system
	taskData data;
	
	filePointer = fopen("trafficShaper.log","a+");
	
	// Starting Message
	printf("emulation begin\n");
	fprintf(filePointer, "emulation begin\n");
	
	LOG_PRINT("emulation begin");
	
	// There should be 11 agruments while calling the application
	if(argc != 11){
		printError();
	}
	
	// Extract the option values from command-line arguments
	while((opt = getopt(argc, argv,":r:R:L:x:t:")) != -1){
		switch(opt){
			case 'r' : data.requestRate 		= atoi(optarg); break; //Assign Request Rate 
			case 'R' : data.noResourceRequired 	= atoi(optarg); break; //Assign Resource Requirement
			case 'L' : data.bufferLength 		= atoi(optarg); break; //Assign Resource Buffer Length
			case 'x' : data.resourceRate 		= atoi(optarg); break; //Assign Resource Rate
			case 't' : data.executionTime 		= atoi(optarg); break; //Assign Execution Time
			default : printError(); break; // Unknown option
		}
	}
	
	// Check for valid values
	if((data.requestRate <=0) || (data.noResourceRequired <= 0) || (data.bufferLength <= 0) \
		|| (data.resourceRate <=0) || (data.executionTime <=0) || (data.bufferLength < data.noResourceRequired)){
		
		printError();
	}
 
	// Create thread for incoming requests
    int retRequest = pthread_create(&requestThread, NULL, requestFun, (void *)&data);
	
	// Create thread for resource tokens
    int retToken = pthread_create(&tokenThread, NULL, tokenFun, (void *)&data);
	
	// Create thread for serving the request 
    int retServer = pthread_create(&serverThread, NULL, serverFun, (void *)&data);
	
	// If threads are created join with main thread.
	if(!retRequest)
		pthread_join(requestThread, NULL);
		
    if(!retToken)
        pthread_join(tokenThread, NULL);
		
    if(!retServer)
        pthread_join(serverThread, NULL);
	
	// Emulation Ends Here	
	printf("emulation ends\n");
	fprintf(filePointer, "emulation ends\n");
 
    return 0;
}

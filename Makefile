OBJS	= requestReceiver.o \
		  tokenReceiver.o \
		  requestServer.o \
		  trafficshaper.o \
		  timeCalculator.o \
		  logger.o
		  
SOURCE	= requestReceiver.cpp \
		  tokenReceiver.cpp \
		  requestServer.cpp \
		  trafficshaper.cpp \
		  timeCalculator.cpp \
		  logger.cpp
		  
HEADER	= trafficShaperResources.h \
		  requestReceiver.h \
		  tokenReceiver.h \
		  requestServer.h \
		  timeCalculator.h \
		  logger.h
		  
OUT		= trafficshaper.exe
LOG 	= trafficshaper.log
CC	 	= g++
FLAGS	= -g -c -Wall
LFLAGS	= 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

requestReceiver.o: requestReceiver.cpp
	$(CC) $(FLAGS) requestReceiver.cpp 

tokenReceiver.o: tokenReceiver.cpp
	$(CC) $(FLAGS) tokenReceiver.cpp 

requestServer.o: requestServer.cpp
	$(CC) $(FLAGS) requestServer.cpp 

trafficshaper.o: trafficshaper.cpp
	$(CC) $(FLAGS) trafficshaper.cpp 
	
timeCalculator.o: timeCalculator.cpp
	$(CC) $(FLAGS) timeCalculator.cpp 
	
timeCalculator.o: logger.cpp
	$(CC) $(FLAGS) logger.cpp 

clean:
	rm -f $(OBJS) $(OUT) $(LOG)

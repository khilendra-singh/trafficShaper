# Project Title

Simulate traffic shaper

This program stores the incoming requests in Q1 which have deterministic resource requirement of R. If enough resources are available, the request is moved to Q2 and if server is not busy it is executed. Each request takes ‘t’ time to execute on the server. The rate at which resource tokens are created is equal to ‘x’. 
If the resource requirement is > L than the request is dropped.
If any argument is not entered or has invalid values, the program notifies the user and gracefully exits.
The program writes the console output into trafficLogger.log file. It also contains a user logger, which can be used by the programmer for debugging the application and analysing the log. The user log is written to logger.txt file.

## Getting Started

The program can be extracted from the attached zip file.

### Building and cleaning the project

The program can be compiled by opening the project directory in the terminal and running make command.
 ```
 eg. TrialUser@TrialPC ~/trafficshaper$ make
 ```
 
All the object files, executable and log files can be cleaned by running 'make clean' command.
 ```
 eg. TrialUser@TrialPC ~/trafficshaper$ make clean
 ```
 
### Running the program

The program can be run by following command

```
./trafficShaper -r r -R R -L L -x x -t t
```
where
 r : Request Rate
 R : Resource Requirement
 L : Resource Buffer Length
 x : Resource Rate
 t : Execution Time

```
./trafficShaper -r 2 -t 5 -R 5 -L 50 -x 1
```

## USER LOGGER

User can add logs in the program for debugging the application

```
LOG_PRINT("Hello World !!!");
```

## Authors

* **Khilendra Singh** - *Initial work*

## License

Not Applicable


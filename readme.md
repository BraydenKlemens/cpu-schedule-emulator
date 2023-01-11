# CPU Scheduler

## About

This project is a c program written for an Operating Systems course. The program emulates a simplified version of a Dispatcher for an OS. The program accepts events from a text file to be simulated, and the program changes states of proccess' in the system accordingly. There are 5 different proccess types and all of them can be serviced out of order.

Events are in the format ```<time> <event> <proccessID> ```
Event types include:
- create proccess
- request resources from another proccess
- interupt from a resource
- timer interupt
- exit process

The output of a program is in the formar ```<process id> <total time Running> <total time Ready> <total time Blocked>```

## Tech Stack
- C Programming language

## How it works
- The program reads in events from a text file
- As the events are read in, each resource state is updated
- The states include ready time, time running and time blocked by other resources

## Execution

In the make file you may change the input file from the test_inputs folder

```
cd cpu-schedule-emulator
make
make run
```

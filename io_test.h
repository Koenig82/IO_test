//operation
#define READ 0
#define WRITE 1

#define NUMBER_OF_THREADS 20

#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

#ifndef _IO_TEST_H_
#define _IO_TEST_H_

//struct containg pointers to information shared by the threads
typedef struct threadArg{

    pthread_barrier_t* barrier;
    double* times;
}threadArg;

//struct containing the threadlocal information
typedef struct {
    int id;
    int operation;
    threadArg* shared;
} threadContext;

void* work(void* args);
double TimeSpecToSeconds(struct timespec* ts);
#endif
//operation
#define WRITE_SMALL 0
#define WRITE_LARGE 1
#define READ_SMALL 2
#define READ_LARGE 3

#define NUMBER_OF_THREADS 20
#define AVERAGE_COUNT 10

#define TEST_SIZE_SMALL 100
#define TEST_SIZE_LARGE 1000000

#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#ifndef _IO_TEST_H_
#define _IO_TEST_H_

//struct containg pointers to information shared by the threads
typedef struct threadArg{
    char* small_data;
    char* large_data;
    pthread_barrier_t* barrier;
    double* times[NUMBER_OF_THREADS];
    FILE* fp[NUMBER_OF_THREADS];
}threadArg;

//struct containing the threadlocal information
typedef struct {
    int* id;
    int* loop_index;
    int* operation;
    threadArg* shared;
} threadContext;

void print_usage(void);
void create_data(threadArg *arg);
double TimeSpecToSeconds(struct timespec* ts);
void collect_results(threadArg *arg, FILE *log);

void* work(void* args);

void write_small(void* args);
void write_large(void* args);
void read_small(void* args);
void read_large(void* args);

#endif
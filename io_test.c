

#include "io_test.h"


int main(int argc, char* argv[]) {

    int index;
    double total_time = 0;
    double average_time;

    //initialize shared threadarguments
    pthread_barrier_t threadBarrier;
    threadArg* arg = malloc(sizeof(threadArg));
    arg->times = malloc(sizeof(double)*NUMBER_OF_THREADS);
    arg->barrier = &threadBarrier;
    pthread_barrier_init(&threadBarrier, NULL, NUMBER_OF_THREADS);

    //initialize threads
    pthread_t* threads = malloc(sizeof(pthread_t)*NUMBER_OF_THREADS);
    threadContext context[NUMBER_OF_THREADS];
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        context[index].shared = arg;
        context[index].id = index;
        if(index < NUMBER_OF_THREADS/2){
            context[index].operation = READ;
        }else{
            context[index].operation = WRITE;
        }
        if(pthread_create(&threads[index], NULL, work, (void*)&context[index])){
            perror("pthread_create: \n");
            exit(EXIT_FAILURE);
        }
    }


    for(index = 0; (unsigned int)index < NUMBER_OF_THREADS; index++){
        if(pthread_join(threads[index], NULL)){
            perror("pthread_join :");
        }
    }
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        printf("\n time: %.12lf for thread %d\n",arg->times[index], index);
        total_time += arg->times[index];
    }

    printf("\nAverage time %.12lf\n", total_time/NUMBER_OF_THREADS);
    free(arg->times);
    free(arg);
    free(threads);
}


void* work(void* args){

    threadContext* context = (threadContext*)args;
    struct timespec start;
    struct timespec end;

    pthread_barrier_wait(context->shared->barrier);

    if(clock_gettime(CLOCK_MONOTONIC, &start)) {
        perror("clock_gettime");
    }

    usleep(200000);  // 200ms

    if(clock_gettime(CLOCK_MONOTONIC, &end)) {
        perror("clock_gettime");
    }

    context->shared->times[context->id] = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);

    return NULL;
}

double TimeSpecToSeconds(struct timespec* ts)
{
    return (double)ts->tv_sec + (double)ts->tv_nsec / 1000000000.0;
}
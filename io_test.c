

#include "io_test.h"
char *file_names[20] = {"thread01",
                        "thread02",
                        "thread03",
                        "thread04",
                        "thread05",
                        "thread06",
                        "thread07",
                        "thread08",
                        "thread09",
                        "thread10",
                        "thread11",
                        "thread12",
                        "thread13",
                        "thread14",
                        "thread15",
                        "thread16",
                        "thread17",
                        "thread18",
                        "thread19",
                        "thread20"};


int main(int argc, char* argv[]) {

    int index;

    //initialize shared threadarguments
    pthread_barrier_t threadBarrier;
    threadArg* arg = malloc(sizeof(threadArg));
    arg->times = malloc(sizeof(double)*NUMBER_OF_THREADS);
    arg->barrier = &threadBarrier;
    pthread_barrier_init(&threadBarrier, NULL, NUMBER_OF_THREADS);
    create_data(arg);

    //Write 20 small files
    pthread_t* threads = malloc(sizeof(pthread_t)*NUMBER_OF_THREADS);
    threadContext context[NUMBER_OF_THREADS];
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        context[index].shared = arg;
        context[index].id = index;
        context[index].operation = WRITE_SMALL;
        if(pthread_create(&threads[index], NULL, work, (void*)&context[index])){
            perror("pthread_create: \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n---Writing 20 small files results---");
    join_and_present_result(threads, context);

    //Write 20 large files
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        context[index].shared = arg;
        context[index].id = index;
        context[index].operation = WRITE_LARGE;
        if(pthread_create(&threads[index], NULL, work, (void*)&context[index])){
            perror("pthread_create: \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n---Writing 20 large files results---");
    join_and_present_result(threads, context);

    //Write 10 small, 10 large
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        context[index].shared = arg;
        context[index].id = index;
        if(index < NUMBER_OF_THREADS/2){
            context[index].operation = WRITE_LARGE;
        }else{
            context[index].operation = WRITE_SMALL;
        }
        if(pthread_create(&threads[index], NULL, work, (void*)&context[index])){
            perror("pthread_create: \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n---Writing 10 small and 10 large files results---");
    join_and_present_result(threads, context);

    //Read 20 small files
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        context[index].shared = arg;
        context[index].id = index;
        context[index].operation = READ_SMALL;
        if(pthread_create(&threads[index], NULL, work, (void*)&context[index])){
            perror("pthread_create: \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n---Reading 20 small files results---");
    join_and_present_result(threads, context);

    //Write 20 large files
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        context[index].shared = arg;
        context[index].id = index;
        context[index].operation = READ_LARGE;
        if(pthread_create(&threads[index], NULL, work, (void*)&context[index])){
            perror("pthread_create: \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n---Reading 20 large files results---");
    join_and_present_result(threads, context);

    //Write 10 large, read 10 large
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        context[index].shared = arg;
        context[index].id = index;
        if(index < NUMBER_OF_THREADS/2){
            context[index].operation = WRITE_LARGE;
        }else{
            context[index].operation = READ_LARGE;
        }
        if(pthread_create(&threads[index], NULL, work, (void*)&context[index])){
            perror("pthread_create: \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n---Writing 10 large and reading 10 large files results---");
    join_and_present_result(threads, context);

    //Write 10 large, read 10 small
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        context[index].shared = arg;
        context[index].id = index;
        if(index < NUMBER_OF_THREADS/2){
            context[index].operation = WRITE_LARGE;
        }else{
            context[index].operation = READ_SMALL;
        }
        if(pthread_create(&threads[index], NULL, work, (void*)&context[index])){
            perror("pthread_create: \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n---Writing 10 large and reading 10 small files results---");
    join_and_present_result(threads, context);

    //Write 10 small, read 10 large
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        context[index].shared = arg;
        context[index].id = index;
        if(index < NUMBER_OF_THREADS/2){
            context[index].operation = WRITE_SMALL;
        }else{
            context[index].operation = READ_LARGE;
        }
        if(pthread_create(&threads[index], NULL, work, (void*)&context[index])){
            perror("pthread_create: \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n---Writing 10 small and reading 10 large files results---");
    join_and_present_result(threads, context);

    //free memory
    pthread_barrier_destroy(&threadBarrier);
    free(arg->small_data);
    free(arg->large_data);
    free(arg->times);
    free(arg);
    free(threads);
}

void create_data(threadArg *arg) {

    if((arg->large_data = malloc(sizeof(char)*1000000)) == NULL){
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }else{
        for(int i = 0; i < 1000000; i++){
            arg->large_data[i] = (char)(rand()%26+65);
        }
    }
    if((arg->small_data = malloc(sizeof(char)*100)) == NULL){
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }else{
        for(int i = 0; i < 100; i++){
            arg->small_data[i] = (char)(rand()%26+65);
        }
    }
}

double TimeSpecToSeconds(struct timespec* ts) {

    return (double)ts->tv_sec + (double)ts->tv_nsec / 1000000000.0;
}

void join_and_present_result(pthread_t *threads, threadContext* arg) {
    int index = 0;
    double total_time = 0;
    for(index = 0; (unsigned int)index < NUMBER_OF_THREADS; index++){
        if(pthread_join(threads[index], NULL)){
            perror("pthread_join :");
        }
    }
    for(index = 0; index < NUMBER_OF_THREADS; index++){
        printf("\n time: %.12lf for thread %d\n",arg->shared->times[index], index+1);
        total_time += arg->shared->times[index];
    }
    printf("\nAverage time %.12lf\n", total_time/NUMBER_OF_THREADS);

}



void* work(void* args){

    threadContext* context = (threadContext*)args;

    switch(context->operation) {

        case WRITE_SMALL  :
            write_small(context);
            break;

        case WRITE_LARGE  :
            write_large(context);
            break;

        case READ_SMALL  :
            read_small(context);
            break;

        case READ_LARGE  :
            read_large(context);
            break;

        default :
            break;
    }

    return NULL;
}

void write_small(void* args){

    threadContext* context = (threadContext*)args;
    char* filename = malloc(sizeof(char)*14);
    strcpy(filename, file_names[context->id]);
    strcat(filename, "Small.txt");
    context->shared->fp[context->id] = fopen(filename, "w");

    struct timespec start;
    struct timespec end;

    pthread_barrier_wait(context->shared->barrier);
    if(clock_gettime(CLOCK_MONOTONIC, &start)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    fputs(context->shared->small_data, context->shared->fp[context->id]);

    if(clock_gettime(CLOCK_MONOTONIC, &end)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    context->shared->times[context->id] = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);
    free(filename);

}

void write_large(void* args){

    threadContext* context = (threadContext*)args;
    char* filename = malloc(sizeof(char)*14);
    strcpy(filename, file_names[context->id]);
    strcat(filename, "Large.txt");

    context->shared->fp[context->id] = fopen(filename, "w");
    if(context->shared->fp[context->id] == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct timespec start;
    struct timespec end;

    pthread_barrier_wait(context->shared->barrier);
    if(clock_gettime(CLOCK_MONOTONIC, &start)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    fputs(context->shared->large_data, context->shared->fp[context->id]);

    if(clock_gettime(CLOCK_MONOTONIC, &end)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    context->shared->times[context->id] = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);
    free(filename);

}

void read_small(void* args){

    threadContext* context = (threadContext*)args;
    char* filename = malloc(sizeof(char)*14);
    strcpy(filename, file_names[context->id]);
    strcat(filename, "Small.txt");
    context->shared->fp[context->id] = fopen(filename, "r");

    struct timespec start;
    struct timespec end;

    char* read_buffer = malloc(sizeof(char)*101);
    pthread_barrier_wait(context->shared->barrier);
    if(clock_gettime(CLOCK_MONOTONIC, &start)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    fgets (read_buffer, 100, context->shared->fp[context->id]);

    if(clock_gettime(CLOCK_MONOTONIC, &end)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    context->shared->times[context->id] = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);
    free(filename);

}

void read_large(void* args){

    threadContext* context = (threadContext*)args;
    char* filename = malloc(sizeof(char)*14);
    strcpy(filename, file_names[context->id]);
    strcat(filename, "Large.txt");
    context->shared->fp[context->id] = fopen(filename, "r");

    struct timespec start;
    struct timespec end;

    char* read_buffer = malloc(sizeof(char)*1000000);
    pthread_barrier_wait(context->shared->barrier);
    if(clock_gettime(CLOCK_MONOTONIC, &start)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    fgets (read_buffer, 1000000, context->shared->fp[context->id]);

    if(clock_gettime(CLOCK_MONOTONIC, &end)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    context->shared->times[context->id] = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);
    free(filename);

}
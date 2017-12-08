

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

    int thread_index;
    int execution_index;
    fclose(fopen("Log.txt", "w"));
    FILE* log = fopen("Log.txt", "a");

    //initialize shared threadarguments
    pthread_barrier_t threadBarrier;
    threadArg* arg = malloc(sizeof(threadArg));
    for(int i = 0; i < AVERAGE_COUNT; i++){
        arg->times[i] = malloc(sizeof(double)*NUMBER_OF_THREADS);
    }
    arg->barrier = &threadBarrier;
    pthread_barrier_init(&threadBarrier, NULL, NUMBER_OF_THREADS);
    create_data(arg);

    //initialize threadlocals
    threadContext context[NUMBER_OF_THREADS];
    for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
        context[thread_index].loop_index = malloc(sizeof(int*));
        context[thread_index].id = malloc(sizeof(int*));
        context[thread_index].operation = malloc(sizeof(int*));
    }

    pthread_t* threads = malloc(sizeof(pthread_t)*NUMBER_OF_THREADS);

    //Write 'nrofthreads' small files
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
            context[thread_index].shared = arg;
            *context[thread_index].loop_index = execution_index;
            *context[thread_index].id = thread_index;
            *context[thread_index].operation = WRITE_SMALL;
            if(pthread_create(&threads[thread_index], NULL, work, (void*)&context[thread_index])){
                perror("pthread_create: \n");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < NUMBER_OF_THREADS; i++){
            if(pthread_join(threads[i], NULL)){
                perror("pthread_join :");
            }
        }
    }
    fprintf(log, "\n---Writing %d small files results---\n", NUMBER_OF_THREADS);
    collect_results(arg, log);

    //Write 'nrofthreads' large files
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
            context[thread_index].shared = arg;
            *context[thread_index].loop_index = execution_index;
            *context[thread_index].id = thread_index;
            *context[thread_index].operation = WRITE_LARGE;
            if(pthread_create(&threads[thread_index], NULL, work, (void*)&context[thread_index])){
                perror("pthread_create: \n");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < NUMBER_OF_THREADS; i++){
            if(pthread_join(threads[i], NULL)){
                perror("pthread_join :");
            }
        }
    }
    fprintf(log, "\n\n---Writing %d large files results---\n", NUMBER_OF_THREADS);
    collect_results(arg, log);

    //Write 'nrofthreads'/2 small and 'nrofthreads'/2 large files
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
            context[thread_index].shared = arg;
            *context[thread_index].loop_index = execution_index;
            *context[thread_index].id = thread_index;
            if(thread_index < NUMBER_OF_THREADS/2){
                *context[thread_index].operation = WRITE_SMALL;
            }else{
                *context[thread_index].operation = WRITE_LARGE;
            }
            if(pthread_create(&threads[thread_index], NULL, work, (void*)&context[thread_index])){
                perror("pthread_create: \n");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < NUMBER_OF_THREADS; i++){
            if(pthread_join(threads[i], NULL)){
                perror("pthread_join :");
            }
        }
    }
    fprintf(log, "\n\n---Writing %d small and %d large files results---\n", NUMBER_OF_THREADS/2, NUMBER_OF_THREADS/2);
    collect_results(arg, log);

    //Read 'nrofthreads' small files
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
            context[thread_index].shared = arg;
            *context[thread_index].loop_index = execution_index;
            *context[thread_index].id = thread_index;
            *context[thread_index].operation = READ_SMALL;
            if(pthread_create(&threads[thread_index], NULL, work, (void*)&context[thread_index])){
                perror("pthread_create: \n");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < NUMBER_OF_THREADS; i++){
            if(pthread_join(threads[i], NULL)){
                perror("pthread_join :");
            }
        }
    }
    fprintf(log, "\n\n---Reading %d small files results---\n", NUMBER_OF_THREADS);
    collect_results(arg, log);

    //Read 'nrofthreads' large files
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
            context[thread_index].shared = arg;
            *context[thread_index].loop_index = execution_index;
            *context[thread_index].id = thread_index;
            *context[thread_index].operation = READ_LARGE;
            if(pthread_create(&threads[thread_index], NULL, work, (void*)&context[thread_index])){
                perror("pthread_create: \n");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < NUMBER_OF_THREADS; i++){
            if(pthread_join(threads[i], NULL)){
                perror("pthread_join :");
            }
        }
    }
    fprintf(log, "\n\n---Reading %d large files results---\n", NUMBER_OF_THREADS);
    collect_results(arg, log);

    //Write and read large files 'nrofthreads'/2 each
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
            context[thread_index].shared = arg;
            *context[thread_index].loop_index = execution_index;
            *context[thread_index].id = thread_index;
            if(thread_index < NUMBER_OF_THREADS/2){
                *context[thread_index].operation = WRITE_LARGE;
            }else{
                *context[thread_index].operation = READ_LARGE;
            }
            if(pthread_create(&threads[thread_index], NULL, work, (void*)&context[thread_index])){
                perror("pthread_create: \n");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < NUMBER_OF_THREADS; i++){
            if(pthread_join(threads[i], NULL)){
                perror("pthread_join :");
            }
        }
    }
    fprintf(log, "\n\n---Writing and reading %d large each results---\n", NUMBER_OF_THREADS/2);
    collect_results(arg, log);

    //Read small and write large 'nrofthreads'/2 each
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
            context[thread_index].shared = arg;
            *context[thread_index].loop_index = execution_index;
            *context[thread_index].id = thread_index;
            if(thread_index < NUMBER_OF_THREADS/2){
                *context[thread_index].operation = READ_SMALL;
            }else{
                *context[thread_index].operation = WRITE_LARGE;
            }
            if(pthread_create(&threads[thread_index], NULL, work, (void*)&context[thread_index])){
                perror("pthread_create: \n");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < NUMBER_OF_THREADS; i++){
            if(pthread_join(threads[i], NULL)){
                perror("pthread_join :");
            }
        }
    }
    fprintf(log, "\n\n---Reading %d small and writing %d large results---\n", NUMBER_OF_THREADS/2, NUMBER_OF_THREADS/2);
    collect_results(arg, log);

    //Write small and read large 'nrofthreads'/2 each
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
            context[thread_index].shared = arg;
            *context[thread_index].loop_index = execution_index;
            *context[thread_index].id = thread_index;
            if(thread_index < NUMBER_OF_THREADS/2){
                *context[thread_index].operation = WRITE_SMALL;
            }else{
                *context[thread_index].operation = READ_LARGE;
            }
            if(pthread_create(&threads[thread_index], NULL, work, (void*)&context[thread_index])){
                perror("pthread_create: \n");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < NUMBER_OF_THREADS; i++){
            if(pthread_join(threads[i], NULL)){
                perror("pthread_join :");
            }
        }
    }
    fprintf(log, "\n\n---Writing %d small and reading %d large results---\n", NUMBER_OF_THREADS/2, NUMBER_OF_THREADS/2);
    collect_results(arg, log);

    //Write, read both small and large 'nrofthreads'/4 each
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
            context[thread_index].shared = arg;
            *context[thread_index].loop_index = execution_index;
            *context[thread_index].id = thread_index;
            if(thread_index < NUMBER_OF_THREADS/4){
                *context[thread_index].operation = WRITE_SMALL;
            }else if(thread_index < NUMBER_OF_THREADS/2){
                *context[thread_index].operation = READ_SMALL;
            }else if(thread_index >= NUMBER_OF_THREADS/2){
                *context[thread_index].operation = WRITE_LARGE;
            }else if(thread_index >= (NUMBER_OF_THREADS/4)*3){
                *context[thread_index].operation = READ_LARGE;
            }
            if(pthread_create(&threads[thread_index], NULL, work, (void*)&context[thread_index])){
                perror("pthread_create: \n");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < NUMBER_OF_THREADS; i++){
            if(pthread_join(threads[i], NULL)){
                perror("pthread_join :");
            }
        }
    }
    fprintf(log, "\n\n---Writing, reading %d small each and writing, reading %d large each results---\n", NUMBER_OF_THREADS/4, NUMBER_OF_THREADS/4);
    collect_results(arg, log);

    //free memory
    pthread_barrier_destroy(&threadBarrier);
    free(arg->small_data);
    free(arg->large_data);
    for(thread_index = 0; thread_index < NUMBER_OF_THREADS; thread_index++){
        free(context[thread_index].loop_index);
        free(context[thread_index].id);
        free(context[thread_index].operation);
    }
    for(execution_index = 0; execution_index < AVERAGE_COUNT; execution_index++){
        free(arg->times[execution_index]);
    }
    free(arg);
    free(threads);
    fclose(log);
}

void create_data(threadArg *arg) {
    int index;
    if((arg->large_data = malloc(sizeof(char)*TEST_SIZE_LARGE)) == NULL){
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }else{
        for(index = 0; index < TEST_SIZE_LARGE; index++){
            arg->large_data[index] = (char)(rand()%26+65);
        }
        arg->large_data[index-1] = '\0';
    }
    if((arg->small_data = malloc(sizeof(char)*TEST_SIZE_SMALL)) == NULL){
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }else{
        for(index = 0; index < TEST_SIZE_SMALL; index++){
            arg->small_data[index] = (char)(rand()%26+65);
        }
        arg->small_data[index-1] = '\0';
    }
}

double TimeSpecToSeconds(struct timespec* ts) {

    return (double)ts->tv_sec + (double)ts->tv_nsec / 1000000000.0;
}

void collect_results(threadArg *arg, FILE *log) {

    int index_thread = 0;
    int index_average_count = 0;

    // Average time for the threads in one execution
    double thread_average = 0;
    // The total time for the execution (highest thread time)
    double total_execution_time = 0;
    // Average of all total execution time over all executions
    double average_execution_time = 0;

    double execution_times[AVERAGE_COUNT];

    for(index_average_count = 0; index_average_count < AVERAGE_COUNT; index_average_count++){

        for(index_thread = 0; index_thread < NUMBER_OF_THREADS; index_thread++){
            /*The line below can add information about individual thread times to the log file*/
            //fprintf(log ,"\n time: %.12lf for thread %d\n",arg->times[index_average_count][index_thread], index_thread+1);
            thread_average += arg->times[index_average_count][index_thread];
            if(arg->times[index_average_count][index_thread] > total_execution_time){
                total_execution_time = arg->times[index_average_count][index_thread];
            }
        }
        execution_times[index_average_count] = total_execution_time;

        /*The lines below can add information about the total time for
         * individual executions, and an average workload distribution between
         * that execution's threads.*/
        fprintf(log, "\nTotal time for all threads in execution %d: %.12lf", index_average_count+1, total_execution_time);
        //fprintf(log, "\nAverage thread work time in execution %d: %.12lf\n", index_average_count+1, thread_average/NUMBER_OF_THREADS);
        total_execution_time = 0;
    }

    for(index_average_count = 0; index_average_count < AVERAGE_COUNT; index_average_count++){
        average_execution_time += execution_times[index_average_count];
    }
    total_execution_time = average_execution_time/AVERAGE_COUNT;
    fprintf(log,"\nAverage execution time over %d executions: %.12lf", AVERAGE_COUNT, total_execution_time);

}



void* work(void* args){

    threadContext* context = (threadContext*)args;

    switch(*context->operation) {

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
    char* filename = malloc(sizeof(char)*18);
    strcpy(filename, file_names[*context->id]);
    strcat(filename, "Small.txt");
    context->shared->fp[*context->id] = fopen(filename, "w");

    struct timespec start;
    struct timespec end;

    pthread_barrier_wait(context->shared->barrier);
    if(clock_gettime(CLOCK_MONOTONIC, &start)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    fputs(context->shared->small_data, context->shared->fp[*context->id]);

    if(clock_gettime(CLOCK_MONOTONIC, &end)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    context->shared->times[*context->loop_index][*context->id] = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);
    fclose(context->shared->fp[*context->id]);
    free(filename);

}


void write_large(void* args){

    threadContext* context = (threadContext*)args;
    char* filename = malloc(sizeof(char)*18);
    strcpy(filename, file_names[*context->id]);
    strcat(filename, "Large.txt");

    context->shared->fp[*context->id] = fopen(filename, "w");
    if(context->shared->fp[*context->id] == NULL) {
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

    fputs(context->shared->large_data, context->shared->fp[*context->id]);

    if(clock_gettime(CLOCK_MONOTONIC, &end)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    context->shared->times[*context->loop_index][*context->id] = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);
    fclose(context->shared->fp[*context->id]);
    free(filename);

}

void read_small(void* args){

    threadContext* context = (threadContext*)args;
    char* filename = malloc(sizeof(char)*18);
    strcpy(filename, file_names[*context->id]);
    strcat(filename, "Small.txt");
    context->shared->fp[*context->id] = fopen(filename, "r");

    struct timespec start;
    struct timespec end;

    char* read_buffer = malloc(sizeof(char)*TEST_SIZE_SMALL);
    pthread_barrier_wait(context->shared->barrier);
    if(clock_gettime(CLOCK_MONOTONIC, &start)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    fgets (read_buffer, TEST_SIZE_SMALL, context->shared->fp[*context->id]);

    if(clock_gettime(CLOCK_MONOTONIC, &end)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    context->shared->times[*context->loop_index][*context->id] = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);
    fclose(context->shared->fp[*context->id]);
    free(filename);
    free(read_buffer);

}

void read_large(void* args){

    threadContext* context = (threadContext*)args;
    char* filename = malloc(sizeof(char)*18);
    strcpy(filename, file_names[*context->id]);
    strcat(filename, "Large.txt");
    context->shared->fp[*context->id] = fopen(filename, "r");

    struct timespec start;
    struct timespec end;

    char* read_buffer = malloc(sizeof(char)*TEST_SIZE_LARGE);
    pthread_barrier_wait(context->shared->barrier);
    if(clock_gettime(CLOCK_MONOTONIC, &start)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    fgets (read_buffer, TEST_SIZE_LARGE, context->shared->fp[*context->id]);

    if(clock_gettime(CLOCK_MONOTONIC, &end)) {
        perror("clock_gettime:");
        exit(EXIT_FAILURE);
    }

    context->shared->times[*context->loop_index][*context->id] = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);
    fclose(context->shared->fp[*context->id]);
    free(filename);
    free(read_buffer);
}

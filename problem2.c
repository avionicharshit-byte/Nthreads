#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 10 // number of threads to create

void *print_thread_id(void *threadid) {
    long tid = (long) threadid;
    printf("Thread %ld: Hello, world!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, print_thread_id, (void *) t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            return -1;
        }
        if (t % 2 == 1) { 
            sleep(10); 
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    return 0;
}

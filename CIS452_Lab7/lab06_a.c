#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void* swapper(void*);

int arr[2];
sem_t mutex;

int main(int argc, char* argv[]) {
    pthread_t who;
    long int loop;

    loop = atoi(argv[1]);

    arr[0] = 0;
    arr[1] = 1;
    sem_init(&mutex, 0, 1);
    pthread_create(&who, NULL, swapper, &loop);
    for (int k = 0; k < loop; k++) {
        sem_wait(&mutex);
        int temp;
        temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
        sem_post(&mutex);
    }
    int rc;
    pthread_join(who, (void **) &rc);
    sem_destroy(&mutex);
    printf ("Values: %5d %5d\n", arr[0], arr[1]);
}

void* swapper(void *arg) {
    long int *num = (long int *) arg;
    for (int k = 0; k < *num; k++) {
        sem_wait(&mutex);
        int temp;
        temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
        sem_post(&mutex);
    }
    return 0;
}
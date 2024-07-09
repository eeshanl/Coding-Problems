#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
uint8_t turn = 0;  // 0 for hello, 1 for world

void* print_hello(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (turn != 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("hello\n");
        fflush(stdout);  // Ensure output is flushed immediately
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        usleep(1000000);  // Sleep for 100ms to simulate some work
    }
    return NULL;
}

void* print_world(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (turn != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("world\n");
        fflush(stdout);  // Ensure output is flushed immediately
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        // usleep(100);  // Sleep for 100ms to simulate some work
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, print_hello, NULL);
    pthread_create(&thread2, NULL, print_world, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
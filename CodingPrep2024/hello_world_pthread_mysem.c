#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// UTILITY CODE

typedef pthread_mutex_t Mutex;
typedef pthread_cond_t Cond;

void perror_exit(char *s) {
    perror(s);
    exit(-1);
}

void *check_malloc(int size) {
    void *p = malloc(size);
    if (p == NULL) perror_exit("malloc failed");
    return p;
}

// MUTEX WRAPPER

Mutex *make_mutex() {
    Mutex *mutex = check_malloc(sizeof(Mutex));
    int n = pthread_mutex_init(mutex, NULL);
    if (n != 0) perror_exit("make_lock failed");
    return mutex;
}

void mutex_destroy(Mutex *mutex) {
    int n = pthread_mutex_destroy(mutex);
    if (n != 0) perror_exit("destroy failed");
}

void mutex_lock(Mutex *mutex) {
    int n = pthread_mutex_lock(mutex);
    if (n != 0) perror_exit("lock failed");
}

void mutex_unlock(Mutex *mutex) {
    int n = pthread_mutex_unlock(mutex);
    if (n != 0) perror_exit("unlock failed");
}

// COND WRAPPER

Cond *make_cond() {
    Cond *cond = check_malloc(sizeof(Cond));
    int n = pthread_cond_init(cond, NULL);
    if (n != 0) perror_exit("make_cond failed");

    return cond;
}

void cond_destroy(Cond *cond) {
    int n = pthread_cond_destroy(cond);
    if (n != 0) perror_exit("cond_destroy failed");
}

void cond_wait(Cond *cond, Mutex *mutex) {
    int n = pthread_cond_wait(cond, mutex);
    if (n != 0) perror_exit("cond_wait failed");
}

void cond_signal(Cond *cond) {
    int n = pthread_cond_signal(cond);
    if (n != 0) perror_exit("cond_signal failed");
}

typedef struct {
    int value, wakeups;
    Mutex *mutex;
    Cond *cond;
} Semaphore;

Semaphore *make_semaphore(int value);
void semaphore_wait(Semaphore *semaphore);
void semaphore_signal(Semaphore *semaphore);

Semaphore *make_semaphore(int value) {
    Semaphore *semaphore = malloc(sizeof(Semaphore));
    semaphore->value = value;
    semaphore->wakeups = 0;
    semaphore->mutex = make_mutex();
    semaphore->cond = make_cond();
    return semaphore;
}

void semaphore_destroy(Semaphore *semaphore) {
    mutex_destroy(semaphore->mutex);
    cond_destroy(semaphore->cond);
    free(semaphore);
}

void semaphore_wait(Semaphore *semaphore) {
    mutex_lock(semaphore->mutex);
    semaphore->value--;

    if (semaphore->value < 0) {
        do {
            cond_wait(semaphore->cond, semaphore->mutex);
        } while (semaphore->wakeups < 1);
        semaphore->wakeups--;
    }
    mutex_unlock(semaphore->mutex);
}

void semaphore_signal(Semaphore *semaphore) {
    mutex_lock(semaphore->mutex);
    semaphore->value++;

    if (semaphore->value <= 0) {
        semaphore->wakeups++;
        cond_signal(semaphore->cond);
    }
    mutex_unlock(semaphore->mutex);
}

Semaphore *sem_hello;
Semaphore *sem_world;

void *print_hello(void *arg) {
    while (1) {
        semaphore_wait(sem_hello);  // Wait for permission to print "hello"
        printf("hello\n");
        fflush(stdout);  // Ensure output is flushed immediately
        // usleep(100000);               // Sleep for 100ms to simulate some
        // work
        semaphore_signal(sem_world);  // Signal that "world" can be printed
        usleep(1000000);
    }
    return NULL;
}

void *print_world(void *arg) {
    while (1) {
        semaphore_wait(sem_world);  // Wait for permission to print "world"
        printf("world\n\n");
        fflush(stdout);  // Ensure output is flushed immediately
        // usleep(1000);                 // Sleep for 100ms to simulate some
        // work
        semaphore_signal(sem_hello);  // Signal that "hello" can be printed
        // usleep(100);
    }
    return NULL;
}

int main() {
    sem_hello = make_semaphore(1);
    sem_world = make_semaphore(0);
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, print_hello, NULL);
    pthread_create(&thread2, NULL, print_world, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    semaphore_destroy(sem_hello);
    semaphore_destroy(sem_world);

    return 0;
}

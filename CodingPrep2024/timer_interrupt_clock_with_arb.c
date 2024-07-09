#include <dispatch/dispatch.h>
#include <pthread.h>
#include <signal.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
        // while (semaphore->wakeups < 1) {
        //     cond_wait(semaphore->cond, semaphore->mutex);
        // }
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

/************************************************************************************************************/

// Atomic ring buffer definition
typedef struct {
    atomic_uint *buffer;
    atomic_uint head;
    atomic_uint tail;
    size_t size;
    Semaphore *sem;
} atomic_ring_buffer_t;

void init_atomic_ring_buffer(atomic_ring_buffer_t *arb, size_t size) {
    arb->buffer = malloc(size * sizeof(atomic_uint));
    for (size_t i = 0; i < size; ++i) {
        atomic_init(&arb->buffer[i], 0);
    }
    atomic_init(&arb->head, 0);
    atomic_init(&arb->tail, 0);
    arb->size = size;
    arb->sem = make_semaphore(0);
}

void destroy_atomic_ring_buffer(atomic_ring_buffer_t *arb) {
    free(arb->buffer);
    semaphore_destroy(arb->sem);
}

uint8_t queue_empty(atomic_ring_buffer_t *arb) {
    return atomic_load_explicit(&arb->head, memory_order_acquire) ==
           atomic_load_explicit(&arb->tail, memory_order_acquire);
}

uint8_t queue_full(atomic_ring_buffer_t *arb) {
    return ((atomic_load_explicit(&arb->head, memory_order_acquire) + 1) %
            arb->size) ==
           atomic_load_explicit(&arb->tail, memory_order_acquire);
}

uint8_t enqueue(atomic_ring_buffer_t *arb, uint32_t value) {
    unsigned int head = atomic_load_explicit(&arb->head, memory_order_acquire);
    unsigned int next_head = (head + 1) % arb->size;

    if (next_head == atomic_load_explicit(&arb->tail, memory_order_acquire)) {
        return 0;  // Buffer is full, cannot enqueue
    }

    atomic_store_explicit(&arb->buffer[head], value, memory_order_release);
    atomic_store_explicit(&arb->head, next_head, memory_order_release);
    return 1;
}

uint8_t dequeue(atomic_ring_buffer_t *arb, uint32_t *value) {
    while (queue_empty(arb)) {
        usleep(1000);  // Sleep for 1ms to avoid busy-waiting
    }

    unsigned int tail = atomic_load_explicit(&arb->tail, memory_order_acquire);
    *value = atomic_load_explicit(&arb->buffer[tail], memory_order_acquire);
    atomic_store_explicit(&arb->tail, (tail + 1) % arb->size,
                          memory_order_release);

    return 1;
}

typedef struct {
    atomic_uint seconds;
    atomic_uint minutes;
    atomic_uint hours;
    atomic_uint days;
} RealWorldClock;

RealWorldClock clocky;
volatile uint32_t counter = 0;
atomic_ring_buffer_t arb;

void init_clocky(RealWorldClock *clocky) {
    atomic_init(&clocky->seconds, 0);
    atomic_init(&clocky->minutes, 0);
    atomic_init(&clocky->hours, 0);
    atomic_init(&clocky->days, 0);
}

// Function to print the current time
void print_clocky() {
    uint32_t days = atomic_load_explicit(&clocky.days, memory_order_acquire);
    uint32_t hours = atomic_load_explicit(&clocky.hours, memory_order_acquire);
    uint32_t minutes =
        atomic_load_explicit(&clocky.minutes, memory_order_acquire);
    uint32_t seconds =
        atomic_load_explicit(&clocky.seconds, memory_order_acquire);

    printf("Clock: %u days, %02u:%02u:%02u\n", days, hours, minutes, seconds);
}

/*
#define NS_PER_SECOND 1000000000
#define SECONDS_PER_MINUTE 60
#define MINUTES_PER_HOUR 60
#define HOURS_PER_DAY 24
#define SECONDS_PER_HOUR (SECONDS_PER_MINUTE * MINUTES_PER_HOUR)
#define SECONDS_PER_DAY (SECONDS_PER_HOUR * HOURS_PER_DAY)
RealWorldClock convert_ns_to_real_world_clock(uint32_t nanoseconds) {
    RealWorldClock clock;

    // Convert nanoseconds to total seconds
    uint32_t total_seconds = nanoseconds / NS_PER_SECOND;

    // Calculate days
    clock.days = total_seconds / SECONDS_PER_DAY;

    // Calculate remaining hours
    total_seconds %= SECONDS_PER_DAY;
    clock.hours = total_seconds / SECONDS_PER_HOUR;

    // Calculate remaining minutes
    total_seconds %= SECONDS_PER_HOUR;
    clock.minutes = total_seconds / SECONDS_PER_MINUTE;

    // Calculate remaining seconds
    clock.seconds = total_seconds % SECONDS_PER_MINUTE;

    return clock;
}

void Timer_IRQHandler(void) {
    // Clear the interrupt flag (this will be hardware-specific)
    // TIMER_ClearInterruptFlag();

    counter++;

    if (counter >= 100) { // 100 * 10ms = 1 second
        counter = 0;
        clock.seconds++;

        if (clock.seconds >= 60) {
            clock.seconds = 0;
            clock.minutes++;

            if (clock.minutes >= 60) {
                clock.minutes = 0;
                clock.hours++;

                if (clock.hours >= 24) {
                    clock.hours = 0;
                    clock.days++;
                }
            }
        }
    }
}
*/
uint32_t queue_counter = 0;

void timer_callback(void *param) {
    // This function will be called every 10ms
    queue_counter++;
    counter++;
    if (counter >= 100) {  // 100 * 10ms = 1 second
        counter = 0;
        // Update the clock
        atomic_fetch_add_explicit(&clocky.seconds, 1, memory_order_acq_rel);

        if (atomic_load_explicit(&clocky.seconds, memory_order_acquire) >= 60) {
            atomic_store_explicit(&clocky.seconds, 0, memory_order_release);
            atomic_fetch_add_explicit(&clocky.minutes, 1, memory_order_acq_rel);

            if (atomic_load_explicit(&clocky.minutes, memory_order_acquire) >=
                60) {
                atomic_store_explicit(&clocky.minutes, 0, memory_order_release);
                atomic_fetch_add_explicit(&clocky.hours, 1,
                                          memory_order_acq_rel);

                if (atomic_load_explicit(&clocky.hours, memory_order_acquire) >=
                    24) {
                    atomic_store_explicit(&clocky.hours, 0,
                                          memory_order_release);
                    atomic_fetch_add_explicit(&clocky.days, 1,
                                              memory_order_acq_rel);
                }
            }
        }
    }
    enqueue(&arb, queue_counter);
    semaphore_signal(arb.sem);
}

// Thread function to print the clock
void *clock_printer_thread(void *arg) {
    while (1) {
        print_clocky();
        usleep(1000000);
    }
    return NULL;
}

void *consumer_thread(void *arg) {
    while (1) {
        uint32_t value = 0;
        semaphore_wait(arb.sem);
        if (dequeue(&arb, &value)) {
            // printf("Consumed: %u\n", value);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    init_atomic_ring_buffer(&arb, 1024);

    init_clocky(&clocky);
    // Create a dispatch queue
    dispatch_queue_t queue = dispatch_queue_create("com.example.timer", 0);

    // Create a dispatch source timer
    dispatch_source_t timer =
        dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);

    // Set the timer to fire every 10ms
    dispatch_source_set_timer(timer, dispatch_time(DISPATCH_TIME_NOW, 0),
                              10 * NSEC_PER_MSEC, 0);

    // Set the event handler
    dispatch_source_set_event_handler_f(timer, timer_callback);
    pthread_t thread_id;

    // Create the thread that prints the clock
    if (pthread_create(&thread_id, NULL, clock_printer_thread, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    pthread_t thread_id2;

    // Create the thread that prints the clock
    if (pthread_create(&thread_id2, NULL, consumer_thread, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Start the timer
    dispatch_resume(timer);

    // Run the main loop
    dispatch_main();
    // Wait for the thread to finish (it won't in this case)
    pthread_join(thread_id, NULL);
    pthread_join(thread_id2, NULL);
    destroy_atomic_ring_buffer(&arb);

    return 0;
}

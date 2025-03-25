#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the bounded buffer

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0, out = 0;      // Buffer indices

sem_t empty;  // Semaphore to track empty slots
sem_t full;   // Semaphore to track filled slots
sem_t mutex;  // Semaphore for mutual exclusion

// Producer function
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {  // Produce 10 items
        item = i + 1;  // Produce an item
        sem_wait(&empty);  // Wait if buffer is full
        sem_wait(&mutex);  // Enter critical section

        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);  // Exit critical section
        sem_post(&full);  // Signal that buffer has a new item

        sleep(1);  // Simulate production time
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {  // Consume 10 items
        sem_wait(&full);  // Wait if buffer is empty
        sem_wait(&mutex);  // Enter critical section

        // Remove the item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);  // Exit critical section
        sem_post(&empty);  // Signal that buffer has an empty slot

        sleep(1);  // Simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // BUFFER_SIZE empty slots initially
    sem_init(&full, 0, 0);             // No filled slots initially
    sem_init(&mutex, 0, 1);            // Binary semaphore for mutual exclusion

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

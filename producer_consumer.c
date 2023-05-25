#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0;              // Index for inserting items into the buffer
int out = 0;             // Index for removing items from the buffer

sem_t empty;           // Semaphore to track empty slots in the buffer
sem_t full;            // Semaphore to track filled slots in the buffer
pthread_mutex_t mutex; // Mutex for mutual exclusion

void *producer(void *arg)
{
    int producerId = *((int *)arg);
    int item;

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        item = rand() % 100; // Generate a random item

        sem_wait(&empty);           // Wait for an empty slot in the buffer
        pthread_mutex_lock(&mutex); // Acquire the mutex lock

        // Insert the item into the buffer
        buffer[in] = item;
        printf("Producer %d produced item: %d\n", producerId, item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Release the mutex lock
        sem_post(&full);              // Signal that a slot in the buffer is full
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int consumerId = *((int *)arg);
    int item;

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        sem_wait(&full);            // Wait for a full slot in the buffer
        pthread_mutex_lock(&mutex); // Acquire the mutex lock

        // Remove an item from the buffer
        item = buffer[out];
        printf("Consumer %d consumed item: %d\n", consumerId, item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Release the mutex lock
        sem_post(&empty);             // Signal that a slot in the buffer is empty
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int producerIds[NUM_PRODUCERS];
    int consumerIds[NUM_CONSUMERS];

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        producerIds[i] = i;
        pthread_create(&producers[i], NULL, producer, (void *)&producerIds[i]);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        consumerIds[i] = i;
        pthread_create(&consumers[i], NULL, consumer, (void *)&consumerIds[i]);
    }

    // Join producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producers[i], NULL);
    }

    // Join consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

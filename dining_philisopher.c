#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (philosopher_id + 1) % NUM_PHILOSOPHERS

int state[NUM_PHILOSOPHERS];
pthread_mutex_t mutex;
pthread_cond_t condition[NUM_PHILOSOPHERS];

void *philosopher(void *arg)
{
    int philosopher_id = *((int *)arg);

    while (1)
    {
        // Philosopher starts thinking
        printf("Philosopher %d is thinking\n", philosopher_id);
        sleep(rand() % 3);

        // Philosopher gets hungry
        printf("Philosopher %d is hungry\n", philosopher_id);

        pthread_mutex_lock(&mutex); // Acquire the mutex lock
        state[philosopher_id] = HUNGRY;
        test(philosopher_id);         // Try to acquire the forks
        pthread_mutex_unlock(&mutex); // Release the mutex lock

        pthread_mutex_lock(&mutex); // Acquire the mutex lock
        while (state[philosopher_id] != EATING)
            pthread_cond_wait(&condition[philosopher_id], &mutex); // Wait until the philosopher starts eating
        pthread_mutex_unlock(&mutex);                              // Release the mutex lock

        // Philosopher is eating
        printf("Philosopher %d is eating\n", philosopher_id);
        sleep(rand() % 3);

        pthread_mutex_lock(&mutex); // Acquire the mutex lock
        state[philosopher_id] = THINKING;
        printf("Philosopher %d finished eating\n", philosopher_id);
        test(LEFT);                   // Check if the left neighbor can eat now
        test(RIGHT);                  // Check if the right neighbor can eat now
        pthread_mutex_unlock(&mutex); // Release the mutex lock
    }
}

void test(int philosopher_id)
{
    if (state[philosopher_id] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[philosopher_id] = EATING;
        pthread_cond_signal(&condition[philosopher_id]); // Signal that the philosopher can start eating
    }
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopherIds[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    // Initialize condition variables
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_cond_init(&condition[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosopherIds[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&philosopherIds[i]);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destroy the mutex

    // Destroy condition variables
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_cond_destroy(&condition[i]);
    }

    return 0;
}

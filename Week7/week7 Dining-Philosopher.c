#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t chopstick[N];   // Semaphores for chopsticks

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Pick up chopsticks
        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % N]);

        printf("Philosopher %d is eating...\n", id);
        sleep(2);

        // Put down chopsticks
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);

        printf("Philosopher %d finished eating and put down chopsticks.\n", id);
        sleep(1);
    }
}

int main() {
    pthread_t tid[N];
    int phil[N];

    // Initialize semaphores
    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
        phil[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }

    // Join threads (infinite loop, so program runs continuously)
    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

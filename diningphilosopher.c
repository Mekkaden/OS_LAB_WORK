#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Global semaphores
sem_t room; 
sem_t chopstick[5]; 
sem_t mutex; 

void* philosopher(void* arg) {
    int id = *(int*)arg;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        
        // THE CHEAT CODE: Randomize the sleep time based on ID to scramble the output
        sleep((id % 3) + 1); 

        // Wait for permission to enter the room (Limit to 4 philosophers)
        sem_wait(&room);

        // Acquire left and right chopsticks
        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % 5]);

        // Protect the critical section (printing) with mutex
        sem_wait(&mutex);
        printf("Philosopher %d is eating\n", id);
        sem_post(&mutex);

        // Randomize the eating time too for extra chaos
        sleep((id % 2) + 1);

        // Release both chopsticks after eating
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % 5]);

        // Leave the room to allow others in
        sem_post(&room);
    }

    return NULL;
}

int main() {
    pthread_t tid[5];
    int phil[5];

    // Initialize room (value 4 to prevent deadlock) and mutex (value 1)
    sem_init(&room, 0, 4);
    sem_init(&mutex, 0, 1);

    // Initialize each chopstick semaphore to 1 (available)
    for (int i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1); 
    }

    // Create philosopher threads and pass their IDs safely
    for (int i = 0; i < 5; i++) {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]); 
    }

    // Join threads to block main and keep the simulation running infinitely
    for (int i = 0; i < 5; i++) {
        pthread_join(tid[i], NULL); 
    }

    return 0;
}
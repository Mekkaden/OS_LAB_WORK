#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 5
// sem_t is used to define a semaphore 
sem_t mutex;      // protects read_count
sem_t rw_mutex;   // protects shared resource
sem_t queue;      // writer priority gate

int read_count = 0;

void *reader(void *arg) { //bcs a thread function should take void * as parameter and return void * -- bcs void * can point to anythign and so the thread can be made any datatype
    int id = *(int *)arg;

    sem_wait(&queue); //if writer , reader is blocked otherwise q = 0 gate closes
    sem_wait(&mutex); //so the readcount is blocked

    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex); //reader can use the resource

    sem_post(&mutex); //free count
    sem_post(&queue); //free queue for other readers to enter

    // ---- Critical Section ----
    printf("Reader %d is READING\n", id);
    sleep(1);
    printf("Reader %d has FINISHED READING\n", id);
    // --------------------------

    //EXITING PART
    
    sem_wait(&mutex); //bcs multiple readers can exit at same time and cause problems 

    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);

    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&queue); //decrements queue
    sem_wait(&rw_mutex); //if reader executing then writer cannot come but since sem_wait(queue) so no more readers can enter the current readers will stop finishing and writer will enter

    // ---- Critical Section ----
    printf("\tWriter %d is WRITING\n", id);
    sleep(2);
    printf("\tWriter %d has FINISHED WRITING\n", id);
    // --------------------------

    sem_post(&rw_mutex);
    sem_post(&queue);

    return NULL;
}

int main() {
    pthread_t r[N], w[N];
    int id[N];

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    sem_init(&queue, 0, 1);

    //this loop creates n reader and writer threads

    for (int i = 0; i < N; i++) {
        id[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &id[i]);    
        pthread_create(&w[i], NULL, writer, &id[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    sem_destroy(&queue);

    return 0;
}
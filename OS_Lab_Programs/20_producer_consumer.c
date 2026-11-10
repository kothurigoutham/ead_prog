/* 20. Producer-Consumer Problem using semaphores (bounded buffer)
   Compile with: gcc 20_producer_consumer.c -o 20_producer_consumer -pthread */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFSIZE   5
#define NPROD     2
#define NCONS     2
#define PER_THREAD 5          /* items produced / consumed by each thread */

int buffer[BUFSIZE];
int in = 0, out = 0, item_counter = 0;

sem_t empty;                  /* counts empty slots */
sem_t full;                   /* counts filled slots */
sem_t mutex;                  /* mutual exclusion on buffer */

void *producer(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < PER_THREAD; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);

        int item = ++item_counter;
        buffer[in] = item;
        printf("Producer %d produced item %d at slot %d\n", id, item, in);
        in = (in + 1) % BUFSIZE;

        sem_post(&mutex);
        sem_post(&full);
        usleep(50000);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < PER_THREAD; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("    Consumer %d consumed item %d from slot %d\n", id, item, out);
        out = (out + 1) % BUFSIZE;

        sem_post(&mutex);
        sem_post(&empty);
        usleep(120000);
    }
    return NULL;
}

int main(void)
{
    pthread_t p[NPROD], c[NCONS];
    int pid[NPROD], cid[NCONS];

    sem_init(&empty, 0, BUFSIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NPROD; i++) {
        pid[i] = i + 1;
        pthread_create(&p[i], NULL, producer, &pid[i]);
    }
    for (int i = 0; i < NCONS; i++) {
        cid[i] = i + 1;
        pthread_create(&c[i], NULL, consumer, &cid[i]);
    }

    for (int i = 0; i < NPROD; i++)
        pthread_join(p[i], NULL);
    for (int i = 0; i < NCONS; i++)
        pthread_join(c[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    printf("\nAll %d items produced and consumed.\n", NPROD * PER_THREAD);
    return 0;
}

/* 19. Reader-Writers Problem using semaphores (readers have priority)
   Compile with: gcc 19_reader_writer.c -o 19_reader_writer -pthread */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NREADERS 3
#define NWRITERS 2
#define ROUNDS   2

sem_t mutex;          /* protects readcount */
sem_t wrt;            /* exclusive access for writers */
int readcount = 0;
int data = 0;         /* shared data */

void *reader(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < ROUNDS; i++) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&wrt);                 /* first reader blocks writers */
        sem_post(&mutex);

        printf("Reader %d reads data = %d  (readers inside: %d)\n", id, data, readcount);
        usleep(100000);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
            sem_post(&wrt);                 /* last reader lets writers in */
        sem_post(&mutex);

        usleep(50000);
    }
    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < ROUNDS; i++) {
        sem_wait(&wrt);
        data++;
        printf("Writer %d wrote data = %d\n", id, data);
        usleep(100000);
        sem_post(&wrt);

        usleep(80000);
    }
    return NULL;
}

int main(void)
{
    pthread_t r[NREADERS], w[NWRITERS];
    int rid[NREADERS], wid[NWRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < NREADERS; i++) {
        rid[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &rid[i]);
    }
    for (int i = 0; i < NWRITERS; i++) {
        wid[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &wid[i]);
    }

    for (int i = 0; i < NREADERS; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < NWRITERS; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    printf("\nDone. Final value of data = %d\n", data);
    return 0;
}

/* 18. Dining Philosophers Problem using semaphores
   Deadlock is avoided by allowing at most N-1 philosophers to try to eat
   at the same time (counting semaphore 'room').
   Compile with: gcc 18_dining_philosophers.c -o 18_dining -pthread */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N      5
#define ROUNDS 2

sem_t chopstick[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    for (int r = 1; r <= ROUNDS; r++) {
        printf("Philosopher %d is thinking\n", id);
        usleep(100000);

        sem_wait(&room);                         /* at most N-1 enter */
        sem_wait(&chopstick[id]);                /* pick left chopstick */
        sem_wait(&chopstick[(id + 1) % N]);      /* pick right chopstick */

        printf("Philosopher %d is EATING (round %d)\n", id, r);
        usleep(150000);
        printf("Philosopher %d finished eating\n", id);

        sem_post(&chopstick[(id + 1) % N]);
        sem_post(&chopstick[id]);
        sem_post(&room);
    }
    return NULL;
}

int main(void)
{
    pthread_t th[N];
    int ids[N];

    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&th[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++)
        pthread_join(th[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&chopstick[i]);
    sem_destroy(&room);

    printf("\nAll philosophers have finished eating. No deadlock.\n");
    return 0;
}

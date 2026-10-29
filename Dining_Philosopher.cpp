#include <stdio.h>

int fork[5] = {1, 1, 1, 1, 1};
int mutex = 1;

void wait(int *S)
{
    while (*S <= 0);
    (*S)--;
}

void signal(int *S)
{
    (*S)++;
}

void philosopher(int i)
{
    int left = i;
    int right = (i + 1) % 5;

    wait(&mutex);

    if (fork[left] == 1 && fork[right] == 1)
    {
        fork[left] = 0;
        fork[right] = 0;

        signal(&mutex);

        printf("Philosopher %d is eating.\n", i + 1);

        fork[left] = 1;
        fork[right] = 1;

        printf("Philosopher %d finished eating.\n", i + 1);
    }
    else
    {
        signal(&mutex);
        printf("Philosopher %d cannot eat. Forks unavailable!\n",
               i + 1);
    }
}

int main()
{
    int choice;

    printf("Dining Philosophers Problem\n");

    while (1)
    {
        printf("\nEnter philosopher number (1-5), 0 to exit: ");
        scanf("%d", &choice);

        if (choice == 0)
            return 0;

        if (choice >= 1 && choice <= 5)
            philosopher(choice - 1);
        else
            printf("Invalid choice!\n");
    }
}

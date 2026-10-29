#include <stdio.h>

int mutex = 1;
int full = 0;
int empty = 5;
int x = 0;

void wait(int *S)
{
    while (*S <= 0);
    (*S)--;
}

void signal(int *S)
{
    (*S)++;
}

void producer()
{
    wait(&empty);
    wait(&mutex);

    x++;
    printf("Producer produces item %d\n", x);

    signal(&mutex);
    signal(&full);
}

void consumer()
{
    wait(&full);
    wait(&mutex);

    printf("Consumer consumes item %d\n", x);
    x--;

    signal(&mutex);
    signal(&empty);
}

int main()
{
    int choice;

    printf("1. Producer\n");
    printf("2. Consumer\n");
    printf("3. Exit\n");

    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (empty > 0)
                    producer();
                else
                    printf("Buffer is full!\n");
                break;

            case 2:
                if (full > 0)
                    consumer();
                else
                    printf("Buffer is empty!\n");
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}


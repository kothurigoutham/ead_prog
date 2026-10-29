#include <stdio.h>

int mutex = 1;
int wrt = 1;
int readcount = 0;
int data = 0;

void wait(int *S)
{
    while (*S <= 0);
    (*S)--;
}

void signal(int *S)
{
    (*S)++;
}

void reader()
{
    wait(&mutex);
    readcount++;

    if (readcount == 1)
        wait(&wrt);

    signal(&mutex);

    printf("Reader is reading data: %d\n", data);

    wait(&mutex);
    readcount--;

    if (readcount == 0)
        signal(&wrt);

    signal(&mutex);
}

void writer()
{
    wait(&wrt);

    data++;
    printf("Writer writes data: %d\n", data);

    signal(&wrt);
}

int main()
{
    int choice;

    printf("Readers-Writers Problem\n");

    while (1)
    {
        printf("\n1. Reader\n");
        printf("2. Writer\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                reader();
                break;

            case 2:
                writer();
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}

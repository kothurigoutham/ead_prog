/* 2. execvp() system call */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *args[] = {"ls", "-l", NULL};

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    if (pid == 0) {
        printf("Child (PID %d): replacing myself with 'ls -l' using execvp\n", getpid());
        fflush(stdout);                 /* flush before the process image is replaced */
        execvp(args[0], args);
        perror("execvp failed");   /* reached only if execvp fails */
        exit(1);
    }
    wait(NULL);
    printf("Parent: child finished, execvp demo complete.\n");
    return 0;
}

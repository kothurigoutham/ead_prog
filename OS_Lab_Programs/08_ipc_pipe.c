/* 8. IPC between a server and multiple clients using a PIPE
   Parent = server, 3 child processes = clients.
   All clients write fixed-size messages into one pipe; the server reads them. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define NCLIENTS 3
#define MSGSZ    64

int main(void)
{
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    for (int i = 1; i <= NCLIENTS; i++) {
        pid_t p = fork();
        if (p < 0) {
            perror("fork");
            exit(1);
        }
        if (p == 0) {                       /* ---- client ---- */
            close(fd[0]);                   /* client does not read */
            char msg[MSGSZ];
            memset(msg, 0, MSGSZ);
            snprintf(msg, MSGSZ, "Hello server, I am client %d (PID %d)", i, getpid());
            write(fd[1], msg, MSGSZ);
            close(fd[1]);
            exit(0);
        }
    }

    /* ---- server ---- */
    close(fd[1]);                           /* server does not write */
    char buf[MSGSZ];
    int count = 0;
    printf("Server: waiting for messages from %d clients...\n", NCLIENTS);
    while (read(fd[0], buf, MSGSZ) == MSGSZ) {
        printf("Server received: %s\n", buf);
        count++;
    }
    close(fd[0]);
    while (wait(NULL) > 0)
        ;
    printf("Server: received %d messages. Done.\n", count);
    return 0;
}

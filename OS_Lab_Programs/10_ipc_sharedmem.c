/* 10. IPC between a server and multiple clients using SHARED MEMORY
   Each client writes into its own slot of the shared segment;
   the server reads all slots after the clients finish. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define NCLIENTS 3
#define SLOTSZ   80

int main(void)
{
    int shmid = shmget(IPC_PRIVATE, NCLIENTS * SLOTSZ, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }

    char *mem = (char *)shmat(shmid, NULL, 0);
    if (mem == (char *)-1) {
        perror("shmat");
        return 1;
    }
    memset(mem, 0, NCLIENTS * SLOTSZ);

    for (int i = 0; i < NCLIENTS; i++) {
        pid_t p = fork();
        if (p < 0) { perror("fork"); exit(1); }
        if (p == 0) {                                   /* ---- client ---- */
            char *slot = mem + i * SLOTSZ;
            snprintf(slot, SLOTSZ, "Message from client %d (PID %d)", i + 1, getpid());
            printf("Client %d wrote to shared memory\n", i + 1);
            shmdt(mem);
            exit(0);
        }
    }

    /* ---- server ---- */
    while (wait(NULL) > 0)                              /* wait for all clients */
        ;
    printf("\nServer reading shared memory:\n");
    for (int i = 0; i < NCLIENTS; i++)
        printf("  Slot %d: %s\n", i + 1, mem + i * SLOTSZ);

    shmdt(mem);
    shmctl(shmid, IPC_RMID, NULL);                      /* remove the segment */
    printf("Server: shared memory removed. Done.\n");
    return 0;
}

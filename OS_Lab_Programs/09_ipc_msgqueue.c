/* 9. IPC between a server and multiple clients using MESSAGE PASSING
   (System V message queue).
   Clients send requests with mtype = 1; the server replies to client i with mtype = 100 + i. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define NCLIENTS 3

struct message {
    long mtype;
    int  id;
    char text[100];
};
#define MSGLEN (sizeof(struct message) - sizeof(long))

int main(void)
{
    int qid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (qid < 0) {
        perror("msgget");
        return 1;
    }

    for (int i = 1; i <= NCLIENTS; i++) {
        pid_t p = fork();
        if (p < 0) { perror("fork"); exit(1); }
        if (p == 0) {                                   /* ---- client ---- */
            struct message m, r;
            m.mtype = 1;
            m.id = i;
            snprintf(m.text, sizeof(m.text), "Request from client %d", i);
            msgsnd(qid, &m, MSGLEN, 0);
            msgrcv(qid, &r, MSGLEN, 100 + i, 0);       /* wait for own reply */
            printf("Client %d got reply : %s\n", i, r.text);
            exit(0);
        }
    }

    /* ---- server ---- */
    for (int k = 0; k < NCLIENTS; k++) {
        struct message m, r;
        msgrcv(qid, &m, MSGLEN, 1, 0);
        printf("Server received     : %s\n", m.text);
        r.mtype = 100 + m.id;
        r.id = 0;
        snprintf(r.text, sizeof(r.text), "Hello client %d, request processed", m.id);
        msgsnd(qid, &r, MSGLEN, 0);
    }

    while (wait(NULL) > 0)
        ;
    msgctl(qid, IPC_RMID, NULL);                        /* remove the queue */
    printf("Server: all clients served. Queue removed.\n");
    return 0;
}

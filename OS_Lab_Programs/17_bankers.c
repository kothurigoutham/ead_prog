/* 17. Banker's Algorithm for Deadlock Avoidance */
#include <stdio.h>

#define MAXP 10
#define MAXR 10

/* Safety algorithm: returns 1 if system is in a safe state and fills seq[] */
int is_safe(int n, int m, int alloc[][MAXR], int need[][MAXR], int avail[], int seq[])
{
    int work[MAXR], finish[MAXP] = {0}, count = 0;

    for (int j = 0; j < m; j++)
        work[j] = avail[j];

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i])
                continue;
            int ok = 1;
            for (int j = 0; j < m; j++)
                if (need[i][j] > work[j]) { ok = 0; break; }
            if (ok) {
                for (int j = 0; j < m; j++)
                    work[j] += alloc[i][j];
                seq[count++] = i;
                finish[i] = 1;
                found = 1;
            }
        }
        if (!found)
            return 0;                       /* no process can proceed: unsafe */
    }
    return 1;
}

int main(void)
{
    int n, m;
    int alloc[MAXP][MAXR], max[MAXP][MAXR], need[MAXP][MAXR], avail[MAXR], seq[MAXP];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);
    if (n < 1 || n > MAXP || m < 1 || m > MAXR) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter Allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available resources (%d values):\n", m);
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nNeed matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    if (is_safe(n, m, alloc, need, avail, seq)) {
        printf("\nSystem is in a SAFE state.\nSafe sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d%s", seq[i], (i < n - 1) ? " -> " : "\n");
    } else {
        printf("\nSystem is in an UNSAFE state (deadlock possible).\n");
        return 0;
    }

    /* Resource-request algorithm */
    int choice;
    printf("\nDo you want to make a resource request? (1 = yes, 0 = no): ");
    if (scanf("%d", &choice) == 1 && choice == 1) {
        int p, req[MAXR];
        printf("Enter process number (0 to %d): ", n - 1);
        scanf("%d", &p);
        if (p < 0 || p >= n) {
            printf("Invalid process number\n");
            return 1;
        }
        printf("Enter request (%d values): ", m);
        for (int j = 0; j < m; j++)
            scanf("%d", &req[j]);

        for (int j = 0; j < m; j++) {
            if (req[j] > need[p][j]) {
                printf("Error: P%d has exceeded its maximum claim.\n", p);
                return 0;
            }
        }
        for (int j = 0; j < m; j++) {
            if (req[j] > avail[j]) {
                printf("P%d must wait: resources not available.\n", p);
                return 0;
            }
        }

        /* pretend to allocate */
        for (int j = 0; j < m; j++) {
            avail[j]    -= req[j];
            alloc[p][j] += req[j];
            need[p][j]  -= req[j];
        }

        if (is_safe(n, m, alloc, need, avail, seq)) {
            printf("Request can be GRANTED. New safe sequence: ");
            for (int i = 0; i < n; i++)
                printf("P%d%s", seq[i], (i < n - 1) ? " -> " : "\n");
        } else {
            printf("Request cannot be granted (it would lead to an unsafe state).\n");
        }
    }
    return 0;
}

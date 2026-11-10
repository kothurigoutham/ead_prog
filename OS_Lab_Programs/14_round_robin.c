/* 14. CPU Scheduling: Round Robin */
#include <stdio.h>

#define MAX 50
#define QS  1000

int main(void)
{
    int n, tq, at[MAX], bt[MAX], rem[MAX], ct[MAX], tat[MAX], wt[MAX];
    int inq[MAX] = {0};
    int queue[QS], front = 0, rear = 0, qcount = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid input\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rem[i] = bt[i];
    }
    printf("Enter time quantum: ");
    if (scanf("%d", &tq) != 1 || tq < 1) {
        printf("Invalid time quantum\n");
        return 1;
    }

    int time = 0, completed = 0;
    printf("\nGantt Chart:\n|");
    while (completed < n) {
        /* add all processes that have arrived to the ready queue */
        for (int i = 0; i < n; i++)
            if (!inq[i] && rem[i] > 0 && at[i] <= time) {
                queue[rear] = i; rear = (rear + 1) % QS; qcount++;
                inq[i] = 1;
            }

        if (qcount == 0) {                  /* CPU idle: jump to next arrival */
            int next = -1;
            for (int i = 0; i < n; i++)
                if (rem[i] > 0 && (next == -1 || at[i] < at[next]))
                    next = i;
            printf(" idle |");
            time = at[next];
            continue;
        }

        int p = queue[front]; front = (front + 1) % QS; qcount--;
        int run = (rem[p] < tq) ? rem[p] : tq;
        printf(" P%d(%d-%d) |", p + 1, time, time + run);
        time += run;
        rem[p] -= run;

        /* processes that arrived while P was running go before P */
        for (int i = 0; i < n; i++)
            if (!inq[i] && rem[i] > 0 && at[i] <= time) {
                queue[rear] = i; rear = (rear + 1) % QS; qcount++;
                inq[i] = 1;
            }

        if (rem[p] > 0) {                   /* not finished: back of the queue */
            queue[rear] = p; rear = (rear + 1) % QS; qcount++;
        } else {
            ct[p]  = time;
            tat[p] = ct[p] - at[p];
            wt[p]  = tat[p] - bt[p];
            avg_tat += tat[p];
            avg_wt  += wt[p];
            completed++;
        }
    }

    printf("\n\nProcess  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < n; i++)
        printf("P%-6d %3d %3d %3d %4d %3d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time    = %.2f\n", avg_wt / n);
    return 0;
}

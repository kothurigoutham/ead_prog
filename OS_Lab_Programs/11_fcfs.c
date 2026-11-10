/* 11. CPU Scheduling: First Come First Served (FCFS) */
#include <stdio.h>

#define MAX 50

int main(void)
{
    int n, at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX], id[MAX];
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid input\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    /* sort by arrival time (stable bubble sort) */
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (at[j] > at[j + 1]) {
                int t;
                t = at[j];  at[j]  = at[j + 1];  at[j + 1]  = t;
                t = bt[j];  bt[j]  = bt[j + 1];  bt[j + 1]  = t;
                t = id[j];  id[j]  = id[j + 1];  id[j + 1]  = t;
            }

    int time = 0;
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        if (time < at[i]) {                 /* CPU idle */
            printf(" idle |");
            time = at[i];
        }
        printf(" P%d |", id[i]);
        time += bt[i];
        ct[i]  = time;
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt  += wt[i];
    }

    printf("\n\nProcess  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < n; i++)
        printf("P%-6d %3d %3d %3d %4d %3d\n", id[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time    = %.2f\n", avg_wt / n);
    return 0;
}

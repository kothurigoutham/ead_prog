/* 16. CPU Scheduling: Non pre-emptive Priority
   (smaller number = higher priority) */
#include <stdio.h>

#define MAX 50

int main(void)
{
    int n, at[MAX], bt[MAX], pr[MAX], ct[MAX], tat[MAX], wt[MAX], done[MAX] = {0};
    int order[MAX], k = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid input\n");
        return 1;
    }
    printf("(Lower number = higher priority)\n");
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
    }

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && at[i] <= time)
                if (idx == -1 || pr[i] < pr[idx] || (pr[i] == pr[idx] && at[i] < at[idx]))
                    idx = i;

        if (idx == -1) {                    /* CPU idle */
            time++;
            continue;
        }
        time += bt[idx];
        ct[idx]  = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx]  = tat[idx] - bt[idx];
        done[idx] = 1;
        order[k++] = idx;
        completed++;
        avg_tat += tat[idx];
        avg_wt  += wt[idx];
    }

    printf("\nExecution order: ");
    for (int i = 0; i < k; i++)
        printf("P%d%s", order[i] + 1, (i < k - 1) ? " -> " : "\n");

    printf("\nProcess  AT  BT  PR  CT  TAT  WT\n");
    for (int i = 0; i < n; i++)
        printf("P%-6d %3d %3d %3d %3d %4d %3d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time    = %.2f\n", avg_wt / n);
    return 0;
}

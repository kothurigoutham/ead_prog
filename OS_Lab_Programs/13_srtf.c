/* 13. CPU Scheduling: Shortest Remaining Time First (SRTF, preemptive SJF) */
#include <stdio.h>

#define MAX 50
#define TL  10000

int main(void)
{
    int n, at[MAX], bt[MAX], rem[MAX], ct[MAX], tat[MAX], wt[MAX];
    static int timeline[TL];
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

    int time = 0, completed = 0;
    while (completed < n && time < TL) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (at[i] <= time && rem[i] > 0)
                if (idx == -1 || rem[i] < rem[idx] || (rem[i] == rem[idx] && at[i] < at[idx]))
                    idx = i;

        timeline[time] = idx;               /* -1 means idle */
        time++;
        if (idx == -1)
            continue;
        rem[idx]--;
        if (rem[idx] == 0) {
            ct[idx]  = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx]  = tat[idx] - bt[idx];
            avg_tat += tat[idx];
            avg_wt  += wt[idx];
            completed++;
        }
    }

    /* print Gantt chart (merge consecutive equal entries) */
    printf("\nGantt Chart:\n|");
    int start = 0;
    for (int t = 1; t <= time; t++) {
        if (t == time || timeline[t] != timeline[start]) {
            if (timeline[start] == -1) printf(" idle (%d-%d) |", start, t);
            else                       printf(" P%d (%d-%d) |", timeline[start] + 1, start, t);
            start = t;
        }
    }

    printf("\n\nProcess  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < n; i++)
        printf("P%-6d %3d %3d %3d %4d %3d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time    = %.2f\n", avg_wt / n);
    return 0;
}

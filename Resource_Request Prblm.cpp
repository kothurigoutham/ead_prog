#include <stdio.h>

int main()
{
    int n, m, i, j, p;
    int allocation[10][10], max[10][10];
    int need[10][10], available[10], request[10];
    int work[10], finish[10] = {0};
    int safeSequence[10], count, found, safe;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &available[j]);

    printf("Enter requesting process number (0 to %d): ", n - 1);
    scanf("%d", &p);

    printf("Enter Request Vector:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &request[j]);

    /* Calculate Need matrix */
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    /* Step 1: Request <= Need */
    for (j = 0; j < m; j++)
    {
        if (request[j] > need[p][j])
        {
            printf("Error: Request exceeds maximum claim.\n");
            return 0;
        }
    }

    /* Step 2: Request <= Available */
    for (j = 0; j < m; j++)
    {
        if (request[j] > available[j])
        {
            printf("Resources unavailable. Process must wait.\n");
            return 0;
        }
    }

    /* Step 3: Pretend to allocate resources */
    for (j = 0; j < m; j++)
    {
        available[j] -= request[j];
        allocation[p][j] += request[j];
        need[p][j] -= request[j];
    }

    /* Run Safety Algorithm */
    for (j = 0; j < m; j++)
        work[j] = available[j];

    count = 0;
    safe = 1;

    while (count < n)
    {
        found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m)
                {
                    for (j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    finish[i] = 1;
                    safeSequence[count++] = i;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            safe = 0;
            break;
        }
    }

    if (safe)
    {
        printf("Request can be GRANTED.\n");
        printf("System remains in a SAFE state.\n");
        printf("Safe Sequence: ");

        for (i = 0; i < n; i++)
            printf("P%d ", safeSequence[i]);

        printf("\n");
    }
    else
    {
        /* Roll back the tentative allocation */
        for (j = 0; j < m; j++)
        {
            available[j] += request[j];
            allocation[p][j] -= request[j];
            need[p][j] += request[j];
        }

        printf("\nRequest cannot be granted.\n");
        printf("System would become unsafe.\n");
        printf("Original resource state restored.\n");
    }

    return 0;
}

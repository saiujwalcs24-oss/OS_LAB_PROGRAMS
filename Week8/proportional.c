#include <stdio.h>

int main()
{
    int n, i, totalWeight = 0, totalCPUTime;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int weight[n];
    float cpuShare[n];

    printf("Enter total CPU time available: ");
    scanf("%d", &totalCPUTime);

    for (i = 0; i < n; i++)
    {
        printf("Enter weight for Process P%d: ", i + 1);
        scanf("%d", &weight[i]);

        totalWeight += weight[i];
    }

    printf("\n--- Proportional Scheduling ---\n");

    for (i = 0; i < n; i++)
    {
        cpuShare[i] =
            ((float)weight[i] / totalWeight) * totalCPUTime;

        printf("Process P%d gets %.2f units of CPU time\n",
               i + 1, cpuShare[i]);
    }

    return 0;
}
#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Maximum Matrix
    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[n], safeSeq[n];
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    int count = 0;

    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {

            if (finish[i] == 0)
            {

                int possible = 1;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if (possible)
                {

                    for (k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }

                    safeSeq[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            break;
        }
    }

    if (count == n)
    {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");

        for (i = 0; i < n; i++)
        {
            printf("P%d ", safeSeq[i]);
        }
    }
    else
    {
        printf("\nSystem is NOT in safe state.\n");
    }

    return 0;
}
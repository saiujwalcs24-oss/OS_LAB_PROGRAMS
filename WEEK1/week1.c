#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
};

int main() {
    int n, i, j;
    struct Process p[20], temp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d Arrival Time: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("P%d Burst Time: ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    // Sort processes by Arrival Time
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Completion Time
    int time = 0;
    for (i = 0; i < n; i++) {
        if (time < p[i].at) {
            time = p[i].at; // CPU idle until process arrives
        }
        time += p[i].bt;
        p[i].ct = time;
    }

    // Calculate TAT, WT, RT
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
        p[i].rt  = p[i].wt; // For FCFS, RT = WT
        avg_wt  += p[i].wt;
        avg_tat += p[i].tat;
    }

    // Display results
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt, p[i].rt);
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}

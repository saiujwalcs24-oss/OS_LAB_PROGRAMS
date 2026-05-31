#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int priority;   // Priority (lower number = higher priority)
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int rt;         // Remaining Time (for preemptive)
    int ct;         // Completion Time
};

void nonPreemptive(int n, struct Process p[]) {
    int time = 0, completed = 0;

    printf("\n--- Non-Preemptive Priority Scheduling ---\n");
    printf("Gantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int minPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].ct == 0 && p[i].priority < minPriority) {
                minPriority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            printf("|P%d", p[idx].pid);
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        } else {
            time++; // idle CPU
            printf("|Idle");
        }
    }
    printf("|\n");

    printf("Process\tAT\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }
}

void preemptive(int n, struct Process p[]) {
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) p[i].rt = p[i].bt;

    printf("\n--- Preemptive Priority Scheduling ---\n");
    printf("Gantt Chart:\n");


        int idx = -1;
        int minPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].priority < minPriority) {
                minPriority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            printf("|P%d", p[idx].pid);
            p[idx].rt--;
            time++;

            if (p[idx].rt == 0) {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else {
            time++;
            printf("|Idle");
        }
    }
    printf("|\n");


    printf("Process\tAT\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time and Priority for Process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].ct = 0;
    }

    printf("\nChoose Scheduling Type:\n1. Non-Preemptive\n2. Preemptive\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
        nonPreemptive(n, p);
    else if (choice == 2)
        preemptive(n, p);
    else
        printf("Invalid choice!\n");

    return 0;
}


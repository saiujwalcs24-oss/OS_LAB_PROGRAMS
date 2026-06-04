#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int rt;         // Remaining Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int at;         // Arrival Time
};

struct Gantt {
    int pid;        // Process ID
    int start;      // Start time
    int end;        // End time
};

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt; // initialize remaining time
        p[i].wt = 0;
        p[i].tat = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    struct Gantt gantt[100]; // store execution order
    int g_index = 0;

    int time = 0; // current time
    int done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) { // only schedule if arrived
                done = 0;
                gantt[g_index].pid = p[i].pid;
                gantt[g_index].start = time;

                if (p[i].rt > quantum) {
                    time += quantum;
                    p[i].rt -= quantum;
                } else {
                    time += p[i].rt;
                    p[i].wt = time - p[i].bt - p[i].at;
                    p[i].rt = 0;
                    p[i].tat = p[i].wt + p[i].bt;
                }

                gantt[g_index].end = time;
                g_index++;
            }
        }

        // If no process has arrived yet, increment time
        int all_waiting = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) {
                all_waiting = 0;
                break;
            }
        }
        if (all_waiting && !done) {
            time++;
        }

    } while (!done);

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < g_index; i++) {
        printf("| P%d ", gantt[i].pid);
    }
    printf("|\n");

    for (int i = 0; i < g_index; i++) {
        printf("%d\t", gantt[i].start);
    }
    printf("%d\n", gantt[g_index - 1].end);

    return 0;
}

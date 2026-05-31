#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

// FCFS Scheduling logic
void calculateFCFS(struct Process p[], int n, int start_time) {
    int time = start_time;

    for (int i = 0; i < n; i++) {
        // If CPU is idle (gap between processes)
        if (time < p[i].arrival_time)
            time = p[i].arrival_time;

        p[i].response_time = time - p[i].arrival_time;
        p[i].completion_time = time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        time = p[i].completion_time;
    }
}

// Updated Print Table to include Averages and return totals
void printTable(struct Process p[], int n, float *total_wt, float *total_tat) {
    *total_wt = 0.0f;
    *total_tat = 0.0f;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        *total_wt += p[i].waiting_time;
        *total_tat += p[i].turnaround_time;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time,
               p[i].waiting_time, p[i].response_time);
    }

    if (n > 0) {
        printf("\nAverage Waiting Time: %.2f", (*total_wt) / n);
        printf("\nAverage Turnaround Time: %.2f\n", (*total_tat) / n);
    } else {
        printf("\nNo processes in this group.\n");
    }
}

// Gantt Chart
void printGantt(struct Process sys[], int ns, struct Process user[], int nu) {
    printf("\nGantt Chart:\n ");

    for (int i = 0; i < ns + nu; i++) printf("------");
    printf("\n|");

    for (int i = 0; i < ns; i++) printf(" P%d |", sys[i].pid);
    for (int i = 0; i < nu; i++) printf(" P%d |", user[i].pid);

    printf("\n ");
    for (int i = 0; i < ns + nu; i++) printf("------");

    printf("\n0");
    for (int i = 0; i < ns; i++) {
        printf("     %d", sys[i].completion_time);
    }
    for (int i = 0; i < nu; i++) {
        printf("     %d", user[i].completion_time);
    }
    printf("\n");
}

int main() {
    int ns, nu;

    printf("Enter number of System processes: ");
    if (scanf("%d", &ns) != 1) return 1;
    struct Process sys[ns];

    for (int i = 0; i < ns; i++) {
        sys[i].pid = i + 1;
        printf("\nSystem Process P%d\n", sys[i].pid);
        printf("Arrival Time: "); scanf("%d", &sys[i].arrival_time);
        printf("Burst Time: ");   scanf("%d", &sys[i].burst_time);
    }

    printf("\nEnter number of User processes: ");
    if (scanf("%d", &nu) != 1) return 1;
    struct Process user[nu];

    for (int i = 0; i < nu; i++) {
        user[i].pid = ns + i + 1;
        printf("\nUser Process P%d\n", user[i].pid);
        printf("Arrival Time: "); scanf("%d", &user[i].arrival_time);
        printf("Burst Time: ");   scanf("%d", &user[i].burst_time);
    }

    // Sort System Processes by AT
    for (int i = 0; i < ns - 1; i++) {
        for (int j = i + 1; j < ns; j++) {
            if (sys[i].arrival_time > sys[j].arrival_time) {
                struct Process temp = sys[i];
                sys[i] = sys[j];
                sys[j] = temp;
            }
        }
    }

    // Sort User Processes by AT
    for (int i = 0; i < nu - 1; i++) {
        for (int j = i + 1; j < nu; j++) {
            if (user[i].arrival_time > user[j].arrival_time) {
                struct Process temp = user[i];
                user[i] = user[j];
                user[j] = temp;
            }
        }
    }

    // Execution Logic
    calculateFCFS(sys, ns, 0);
    int last_time = (ns > 0) ? sys[ns - 1].completion_time : 0;
    calculateFCFS(user, nu, last_time);

    // Output
    printf("\n==============================");
    printf("\n--- SYSTEM PROCESSES ---");
    float total_wt_sys = 0.0f, total_tat_sys = 0.0f;
    printTable(sys, ns, &total_wt_sys, &total_tat_sys);

    printf("\n--- USER PROCESSES ---");
    float total_wt_user = 0.0f, total_tat_user = 0.0f;
    printTable(user, nu, &total_wt_user, &total_tat_user);

    // Combined averages for all processes
    int total_n = ns + nu;
    float total_wt_all = total_wt_sys + total_wt_user;
    float total_tat_all = total_tat_sys + total_tat_user;

    if (total_n > 0) {
        printf("\n--- ALL PROCESSES ---");
        printf("\nOverall Average Waiting Time: %.2f", total_wt_all / total_n);
        printf("\nOverall Average Turnaround Time: %.2f\n", total_tat_all / total_n);
    } else {
        printf("\nNo processes to compute overall averages.\n");
    }

    printf("\n==============================");
    printGantt(sys, ns, user, nu);

    return 0;
}

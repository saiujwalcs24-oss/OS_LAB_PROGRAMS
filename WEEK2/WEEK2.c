#include <stdio.h>
#include <limits.h>

// Structure to hold all process metrics
struct Process {
int pid; // Process ID
int at; // Arrival Time
int bt; // Burst Time
int rem_bt; // Remaining Burst Time (Used for Preemptive)
int ct; // Completion Time
int tat; // Turn Around Time
int wt; // Waiting Time
int rt; // Response Time
};

// Helper function to print the Gantt Chart nicely
void printGanttChart(int gantt_pid[], int gantt_start[], int gantt_end[], int g_idx) {
printf("\n--- Gantt Chart ---\n ");

// Top border
for (int i = 0; i < g_idx; i++) printf("--------");
printf("\n|");

// Process IDs
for (int i = 0; i < g_idx; i++) {
if (gantt_pid[i] == -1) printf(" IDLE |");
else printf(" P%-2d |", gantt_pid[i]);
}
printf("\n ");

// Bottom border
for (int i = 0; i < g_idx; i++) printf("--------");
printf("\n");

// Timeline
printf("%-8d", gantt_start[0]);
for (int i = 0; i < g_idx; i++) {
printf("%-8d", gantt_end[i]);
}
printf("\n");
}

// Function for Non-Preemptive SJF
void nonPreemptiveSJF(struct Process p[], int n) {
int is_completed[100] = {0};
int current_time = 0, completed = 0;
float total_tat = 0, total_wt = 0, total_rt = 0;

// Gantt chart tracking arrays
int gantt_pid[1000], gantt_start[1000], gantt_end[1000];
int g_idx = 0;

printf("\n--- Results: Non-Preemptive SJF ---\n");

while (completed != n) {
int idx = -1;
int min_bt = INT_MAX;

for (int i = 0; i < n; i++) {
if (p[i].at <= current_time && is_completed[i] == 0) {
if (p[i].bt < min_bt) {
min_bt = p[i].bt;
idx = i;
}
if (p[i].bt == min_bt) {
if (p[i].at < p[idx].at) {
idx = i;
}
}
}
}

if (idx != -1) {
// Gantt chart tracking
gantt_pid[g_idx] = p[idx].pid;
gantt_start[g_idx] = current_time;
gantt_end[g_idx] = current_time + p[idx].bt;
g_idx++;

// Process Metrics
p[idx].rt = current_time - p[idx].at;
p[idx].ct = current_time + p[idx].bt;
p[idx].tat = p[idx].ct - p[idx].at;
p[idx].wt = p[idx].tat - p[idx].bt;

total_tat += p[idx].tat;
total_wt += p[idx].wt;
total_rt += p[idx].rt;

current_time += p[idx].bt;
is_completed[idx] = 1;
completed++;
} else {
// Handle CPU Idle time for Gantt chart
if (g_idx == 0 || gantt_pid[g_idx - 1] != -1) {
gantt_pid[g_idx] = -1; // -1 represents IDLE
gantt_start[g_idx] = current_time;
gantt_end[g_idx] = current_time + 1;
g_idx++;
} else {
gantt_end[g_idx - 1] = current_time + 1;
}
current_time++;
}
}

printGanttChart(gantt_pid, gantt_start, gantt_end, g_idx);

// Print Results Table
printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
for (int i = 0; i < n; i++) {
printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
}
printf("\nAverage Turn Around Time: %.2f", total_tat / n);
printf("\nAverage Waiting Time: %.2f", total_wt / n);
printf("\nAverage Response Time: %.2f\n", total_rt / n);
}

// Function for Preemptive SJF (SRTF)
void preemptiveSJF(struct Process p[], int n) {
int is_completed[100] = {0};
int current_time = 0, completed = 0;
float total_tat = 0, total_wt = 0, total_rt = 0;

// Gantt chart tracking arrays
int gantt_pid[1000], gantt_start[1000], gantt_end[1000];
int g_idx = 0;

printf("\n--- Results: Preemptive SJF (SRTF) ---\n");

while (completed != n) {
int idx = -1;
int min_rem_bt = INT_MAX;

for (int i = 0; i < n; i++) {
if (p[i].at <= current_time && is_completed[i] == 0) {
if (p[i].rem_bt < min_rem_bt) {
min_rem_bt = p[i].rem_bt;
idx = i;
}
if (p[i].rem_bt == min_rem_bt) {
if (p[i].at < p[idx].at) {
idx = i;
}
}
}
}

int current_pid = (idx != -1) ? p[idx].pid : -1;

// Gantt chart logic: consolidate contiguous blocks
if (g_idx == 0 || gantt_pid[g_idx - 1] != current_pid) {
gantt_pid[g_idx] = current_pid;
gantt_start[g_idx] = current_time;
gantt_end[g_idx] = current_time + 1;
g_idx++;
} else {
gantt_end[g_idx - 1] = current_time + 1;
}

if (idx != -1) {
// First time getting CPU
if (p[idx].rem_bt == p[idx].bt) {
p[idx].rt = current_time - p[idx].at;
}

p[idx].rem_bt--;
current_time++;

// Process finished
if (p[idx].rem_bt == 0) {
p[idx].ct = current_time;
p[idx].tat = p[idx].ct - p[idx].at;
p[idx].wt = p[idx].tat - p[idx].bt;

total_tat += p[idx].tat;
total_wt += p[idx].wt;
total_rt += p[idx].rt;

is_completed[idx] = 1;
completed++;
}
} else {
current_time++;
}
}

printGanttChart(gantt_pid, gantt_start, gantt_end, g_idx);

// Print Results Table
printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
for (int i = 0; i < n; i++) {
printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
}
printf("\nAverage Turn Around Time: %.2f", total_tat / n);
printf("\nAverage Waiting Time: %.2f", total_wt / n);
printf("\nAverage Response Time: %.2f\n", total_rt / n);
}

int main() {
int n, choice;

printf("Enter number of processes: ");
scanf("%d", &n);

struct Process p[n];

// Gather inputs
for (int i = 0; i < n; i++) {
p[i].pid = i + 1;
printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
scanf("%d %d", &p[i].at, &p[i].bt);
p[i].rem_bt = p[i].bt; // Initialize remaining time for preemptive case
}

// Menu using switch case
printf("\nSelect the Scheduling Algorithm:\n");
printf("1. Non-Preemptive Shortest Job First (SJF)\n");
printf("2. Preemptive Shortest Job First (SRTF)\n");
printf("Enter your choice (1 or 2): ");
scanf("%d", &choice);

switch(choice) {
case 1:
nonPreemptiveSJF(p, n);
break;
case 2:
preemptiveSJF(p, n);
break;
default:
printf("Invalid choice! Please run the program again and select 1 or 2.\n");
}

return 0;
}

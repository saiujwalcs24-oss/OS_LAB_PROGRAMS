#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int execution_time;
    int period;
    int deadline;
    int remaining_time;
} Task;

void rate_monotonic(Task tasks[], int n, int hyperperiod) {
    printf("\n--- Rate Monotonic Scheduling ---\n");
    for (int t = 0; t < hyperperiod; t++) {
        int chosen = -1;
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].deadline = t + tasks[i].period;
            }
            if (tasks[i].remaining_time > 0) {
                if (chosen == -1 || tasks[i].period < tasks[chosen].period)
                    chosen = i;
            }
        }
        if (chosen != -1) {
            tasks[chosen].remaining_time--;
            printf("Time %d: Task %d running\n", t, tasks[chosen].id);
        } else {
            printf("Time %d: CPU idle\n", t);
        }
    }
}

int main() {
    Task tasks[] = {
        {1, 1, 4, 0, 0},
        {2, 2, 5, 0, 0}
    };
    int n = 2;
    int hyperperiod = 20;
    rate_monotonic(tasks, n, hyperperiod);
    return 0;
}

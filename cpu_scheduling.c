/*----------------------------------------------------------
CPU Scheduling is the process of deciding which process will use the CPU at a given time.
It improves CPU utilization and system efficiency.

Non-preemptive scheduling means once a process starts execution, 
it cannot be stopped until it completes. 

Here, we implement:
1. FCFS (First Come First Serve)
   - Processes are executed in the order they arrive.
2. SJF (Shortest Job First)
   - The process with the smallest burst time executes first.
3. Priority Scheduling
   - Process with the highest priority (lowest number) runs first.
4. Round Robin
   - Each process gets a fixed time slice (quantum) cyclically.
   - It is technically preemptive, but often compared alongside others.

Each algorithm calculates:
- Turnaround Time = Completion Time – Arrival Time
- Waiting Time    = Turnaround Time – Burst Time
----------------------------------------------------------
*/

#include <stdio.h>

struct Process {
    int pid;
    int burst;
    int arrival;
    int priority;
    int waiting;
    int turnaround;
};

void findAvgTime(struct Process p[], int n) {
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

void FCFS(struct Process p[], int n) {
    printf("\n--- FCFS Scheduling ---\n");
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival) time = p[i].arrival;
        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = time - p[i].arrival;
        printf("P%d: Waiting=%d Turnaround=%d\n", p[i].pid, p[i].waiting, p[i].turnaround);
    }
    findAvgTime(p, n);
}

void SJF(struct Process p[], int n) {
    printf("\n--- SJF Scheduling ---\n");
    int completed = 0, time = 0, min;
    int isCompleted[10] = {0};
    while (completed != n) {
        min = -1;
        int shortest = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !isCompleted[i] && p[i].burst < shortest) {
                shortest = p[i].burst;
                min = i;
            }
        }
        if (min == -1) {
            time++;
            continue;
        }
        time += p[min].burst;
        p[min].turnaround = time - p[min].arrival;
        p[min].waiting = p[min].turnaround - p[min].burst;
        isCompleted[min] = 1;
        completed++;
        printf("P%d: Waiting=%d Turnaround=%d\n", p[min].pid, p[min].waiting, p[min].turnaround);
    }
    findAvgTime(p, n);
}

void PriorityScheduling(struct Process p[], int n) {
    printf("\n--- Priority Scheduling ---\n");
    int completed = 0, time = 0;
    int isCompleted[10] = {0};
    while (completed != n) {
        int idx = -1, highest = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !isCompleted[i] && p[i].priority < highest) {
                highest = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        time += p[idx].burst;
        p[idx].turnaround = time - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        isCompleted[idx] = 1;
        completed++;
        printf("P%d: Waiting=%d Turnaround=%d\n", p[idx].pid, p[idx].waiting, p[idx].turnaround);
    }
    findAvgTime(p, n);
}

void RoundRobin(struct Process p[], int n, int quantum) {
    printf("\n--- Round Robin Scheduling ---\n");
    int rem_bt[10];
    for (int i = 0; i < n; i++) rem_bt[i] = p[i].burst;
    int t = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    p[i].waiting = t - p[i].burst - p[i].arrival;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
    for (int i = 0; i < n; i++)
        p[i].turnaround = p[i].burst + p[i].waiting;
    for (int i = 0; i < n; i++)
        printf("P%d: Waiting=%d Turnaround=%d\n", p[i].pid, p[i].waiting, p[i].turnaround);
    findAvgTime(p, n);
}

int main() {
    int n, quantum;
    struct Process p[10];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for P%d: ", i + 1);
        scanf("%d%d%d", &p[i].arrival, &p[i].burst, &p[i].priority);
    }
    FCFS(p, n);
    SJF(p, n);
    PriorityScheduling(p, n);
    printf("\nEnter Time Quantum for Round Robin: ");
    scanf("%d", &quantum);
    RoundRobin(p, n, quantum);
    return 0;
}

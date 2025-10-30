/*
Multi-level queue with two queues:
- System processes (higher priority)
- User processes (lower priority)
We use FCFS within each queue. Scheduler runs all ready system processes first (in arrival order),
then runs user processes (arrival order). Calculate waiting and turnaround times.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pid;
    int arrival;
    int burst;
    int isSystem; // 1=system, 0=user
    int waiting, turnaround, completion;
} Proc;

int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    Proc p[n];
    for(int i=0;i<n;i++){
        p[i].pid = i+1;
        printf("For P%d enter arrival, burst, type(1=system,0=user): ", p[i].pid);
        scanf("%d%d%d",&p[i].arrival,&p[i].burst,&p[i].isSystem);
        p[i].waiting = p[i].turnaround = p[i].completion = 0;
    }
    // split into two arrays maintaining arrival order
    Proc sys[n]; int sc=0;
    Proc usr[n]; int uc=0;
    for(int t=0;t<n;t++){
        // stable insertion by arrival
        for(int i=0;i<n;i++){
            // We'll collect in order of pid but we must consider arrival; easier: sort by arrival first
        }
    }
    // Sort original list by arrival
    for(int i=0;i<n-1;i++) for(int j=i+1;j<n;j++)
        if(p[i].arrival > p[j].arrival){
            Proc tmp=p[i]; p[i]=p[j]; p[j]=tmp;
        }
    for(int i=0;i<n;i++){
        if(p[i].isSystem) sys[sc++]=p[i];
        else usr[uc++]=p[i];
    }
    int time=0;
    printf("\nExecution order & times:\n");
    // run system queue FCFS
    for(int i=0;i<sc;i++){
        if(time < sys[i].arrival) time = sys[i].arrival;
        sys[i].waiting = time - sys[i].arrival;
        time += sys[i].burst;
        sys[i].completion = time;
        sys[i].turnaround = sys[i].completion - sys[i].arrival;
        printf("System P%d: WT=%d TAT=%d\n", sys[i].pid, sys[i].waiting, sys[i].turnaround);
    }
    // run user queue FCFS
    for(int i=0;i<uc;i++){
        if(time < usr[i].arrival) time = usr[i].arrival;
        usr[i].waiting = time - usr[i].arrival;
        time += usr[i].burst;
        usr[i].completion = time;
        usr[i].turnaround = usr[i].completion - usr[i].arrival;
        printf("User   P%d: WT=%d TAT=%d\n", usr[i].pid, usr[i].waiting, usr[i].turnaround);
    }
    // averages
    double tw=0, tt=0;
    for(int i=0;i<sc;i++){ tw += sys[i].waiting; tt += sys[i].turnaround;}
    for(int i=0;i<uc;i++){ tw += usr[i].waiting; tt += usr[i].turnaround;}
    printf("\nAverage Waiting = %.2f\nAverage Turnaround = %.2f\n", tw/n, tt/n);
    return 0;
}

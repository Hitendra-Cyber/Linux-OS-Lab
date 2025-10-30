/*
Simulates FCFS and SSTF disk head scheduling.
Input: request queue and initial head position.
FCFS processes in given order; SSTF picks the request with minimum seek distance from current head.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fcfs(int req[], int n, int head){
    printf("\nFCFS order: %d", head);
    int seek=0;
    int cur=head;
    for(int i=0;i<n;i++){
        seek += abs(req[i]-cur);
        cur = req[i];
        printf(" -> %d", cur);
    }
    printf("\nTotal seek = %d\n", seek);
}

void sstf(int req[], int n, int head){
    int visited[n]; for(int i=0;i<n;i++) visited[i]=0;
    int cur=head;
    int seek=0;
    printf("\nSSTF order: %d", head);
    for(int k=0;k<n;k++){
        int idx=-1, minD=1e9;
        for(int i=0;i<n;i++){
            if(!visited[i] && abs(req[i]-cur) < minD){ minD = abs(req[i]-cur); idx=i; }
        }
        if(idx==-1) break;
        visited[idx]=1;
        seek += minD;
        cur = req[idx];
        printf(" -> %d", cur);
    }
    printf("\nTotal seek = %d\n", seek);
}

int main(){
    int n; printf("Number of requests: "); scanf("%d",&n);
    int req[n];
    for(int i=0;i<n;i++){ printf("Req %d: ", i+1); scanf("%d",&req[i]); }
    int head; printf("Initial head position: "); scanf("%d",&head);
    fcfs(req,n,head);
    sstf(req,n,head);
    return 0;
}

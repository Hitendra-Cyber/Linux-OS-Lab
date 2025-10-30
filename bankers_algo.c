/*
Implements Dijkstra's Banker's algorithm to determine if the system is in a safe state.
User inputs number of processes, resources, Allocation and Max matrices.
If a safe sequence exists, it is displayed; otherwise, a deadlock warning is shown.
*/

#include <stdio.h>
#include <string.h>
#define MAXP 10
#define MAXR 10

int main(){
    int n, m; 
    printf("Processes: "); scanf("%d",&n);
    printf("Resources: "); scanf("%d",&m);
    int alloc[MAXP][MAXR], max[MAXP][MAXR], avail[MAXR];
    for(int i=0;i<n;i++){
        printf("Allocation for P%d: ", i);
        for(int j=0;j<m;j++) scanf("%d",&alloc[i][j]);
    }
    for(int i=0;i<n;i++){
        printf("Max for P%d: ", i);
        for(int j=0;j<m;j++) scanf("%d",&max[i][j]);
    }
    printf("Available: ");
    for(int j=0;j<m;j++) scanf("%d",&avail[j]);
    int need[MAXP][MAXR];
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) need[i][j] = max[i][j] - alloc[i][j];
    int finish[MAXP]; memset(finish,0,sizeof(finish));
    int safeSeq[MAXP]; int idx=0;
    int work[MAXR];
    for(int j=0;j<m;j++) work[j]=avail[j];
    for(int k=0;k<n;k++){
        int found=0;
        for(int i=0;i<n;i++){
            if(!finish[i]){
                int ok=1;
                for(int j=0;j<m;j++) if(need[i][j] > work[j]) { ok=0; break; }
                if(ok){
                    for(int j=0;j<m;j++) work[j]+=alloc[i][j];
                    safeSeq[idx++]=i; finish[i]=1; found=1;
                }
            }
        }
        if(!found) break;
    }
    int all=1; for(int i=0;i<n;i++) if(!finish[i]) all=0;
    if(all){
        printf("System is in SAFE state.\nSafe sequence: ");
        for(int i=0;i<n;i++) printf("P%d ", safeSeq[i]);
        printf("\n");
    } else printf("System NOT in safe state. Deadlock possible.\n");
    return 0;
}

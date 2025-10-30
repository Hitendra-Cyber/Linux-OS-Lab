/*
Simulates three contiguous fit algorithms:
- First-fit: allocate in the first partition large enough.
- Best-fit: allocate in the smallest partition that fits.
- Worst-fit: allocate in the largest partition.
We input partitions (holes) and process sizes.
*/

#include <stdio.h>
#include <string.h>
#define MAXP 20

void first_fit(int parts[], int m, int proc[], int n){
    int alloc[MAXP]; for(int i=0;i<n;i++) alloc[i]=-1;
    int part_used[MAXP]={0};
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!part_used[j] && parts[j] >= proc[i]){ alloc[i]=j; part_used[j]=1; break;}
        }
    }
    printf("\nFirst-fit results:\n");
    for(int i=0;i<n;i++){
        if(alloc[i]==-1) printf("Proc %d (size %d): Not allocated\n", i+1, proc[i]);
        else printf("Proc %d (size %d): Partition %d (size %d)\n", i+1, proc[i], alloc[i]+1, parts[alloc[i]]);
    }
}

void best_fit(int parts[], int m, int proc[], int n){
    int alloc[MAXP]; for(int i=0;i<n;i++) alloc[i]=-1;
    int part_used[MAXP]={0};
    for(int i=0;i<n;i++){
        int best=-1;
        for(int j=0;j<m;j++){
            if(!part_used[j] && parts[j] >= proc[i]){
                if(best==-1 || parts[j] < parts[best]) best=j;
            }
        }
        if(best!=-1){ alloc[i]=best; part_used[best]=1; }
    }
    printf("\nBest-fit results:\n");
    for(int i=0;i<n;i++){
        if(alloc[i]==-1) printf("Proc %d: Not allocated\n", i+1);
        else printf("Proc %d: Partition %d (size %d)\n", i+1, alloc[i]+1, parts[alloc[i]]);
    }
}

void worst_fit(int parts[], int m, int proc[], int n){
    int alloc[MAXP]; for(int i=0;i<n;i++) alloc[i]=-1;
    int part_used[MAXP]={0};
    for(int i=0;i<n;i++){
        int worst=-1;
        for(int j=0;j<m;j++){
            if(!part_used[j] && parts[j] >= proc[i]){
                if(worst==-1 || parts[j] > parts[worst]) worst=j;
            }
        }
        if(worst!=-1){ alloc[i]=worst; part_used[worst]=1; }
    }
    printf("\nWorst-fit results:\n");
    for(int i=0;i<n;i++){
        if(alloc[i]==-1) printf("Proc %d: Not allocated\n", i+1);
        else printf("Proc %d: Partition %d (size %d)\n", i+1, alloc[i]+1, parts[alloc[i]]);
    }
}

int main(){
    int m; printf("Enter number of partitions: "); scanf("%d",&m);
    int parts[m];
    for(int i=0;i<m;i++){ printf("Partition %d size: ", i+1); scanf("%d",&parts[i]); }
    int n; printf("Enter number of processes: "); scanf("%d",&n);
    int proc[n]; for(int i=0;i<n;i++){ printf("Process %d size: ", i+1); scanf("%d",&proc[i]); }
    first_fit(parts,m,proc,n);
    best_fit(parts,m,proc,n);
    worst_fit(parts,m,proc,n);
    return 0;
}

/*
MVT (Multiprogramming with Variable Tasks): allocate variable-sized holes (first-fit used here).
MFT (Multiprogramming with Fixed Tasks): partition memory into fixed partitions; allocate based on partition sizes.
This program provides simple simulations for both.
*/

#include <stdio.h>
#include <string.h>
#define MAXP 20
#define MAX_PART 10

/* MVT using simple first-fit */
void mvt_sim(){
    int memSize;
    printf("\nMVT Simulation (Variable partitions - first fit)\nEnter memory size: ");
    scanf("%d",&memSize);
    int m = memSize;
    int n;
    printf("Enter number of processes: "); scanf("%d",&n);
    int proc[MAXP];
    for(int i=0;i<n;i++){ printf("Proc %d size: ", i+1); scanf("%d",&proc[i]); }
    int allocated[MAXP]; memset(allocated, -1, sizeof(allocated));
    // simple free list as array of holes: initially one hole at 0 size memSize
    int holeStart[MAXP], holeSize[MAXP], holeCount=1;
    holeStart[0]=0; holeSize[0]=memSize;
    for(int i=0;i<n;i++){
        int found=-1;
        for(int h=0;h<holeCount;h++){
            if(holeSize[h] >= proc[i]){ found=h; break; }
        }
        if(found==-1){ printf("Process %d cannot be allocated (no hole)\n", i+1); continue; }
        allocated[i] = holeStart[found];
        holeStart[found] += proc[i];
        holeSize[found] -= proc[i];
        if(holeSize[found]==0){
            // remove hole
            for(int k=found;k<holeCount-1;k++){ holeStart[k]=holeStart[k+1]; holeSize[k]=holeSize[k+1]; }
            holeCount--;
        }
        printf("Proc %d allocated at %d\n", i+1, allocated[i]);
    }
}

/* MFT using fixed partitions */
void mft_sim(){
    int partCount;
    printf("\nMFT Simulation (Fixed partitions)\nEnter number of partitions: ");
    scanf("%d",&partCount);
    int part[MAX_PART], used[MAX_PART];
    for(int i=0;i<partCount;i++){ printf("Partition %d size: ", i+1); scanf("%d",&part[i]); used[i]=0; }
    int p;
    printf("Enter number of processes: "); scanf("%d",&p);
    int proc[MAXP];
    for(int i=0;i<p;i++) { printf("Proc %d size: ", i+1); scanf("%d",&proc[i]); }
    for(int i=0;i<p;i++){
        int found=-1;
        for(int j=0;j<partCount;j++){
            if(!used[j] && part[j] >= proc[i]){ found=j; break; }
        }
        if(found==-1) printf("Process %d cannot be allocated\n", i+1);
        else { used[found]=1; printf("Process %d allocated to partition %d (part size %d)\n", i+1, found+1, part[found]); }
    }
}

int main(){
    int ch;
    while(1){
        printf("\n1.MVT 2.MFT 3.Exit\nChoice: "); if(scanf("%d",&ch)!=1) break;
        if(ch==1) mvt_sim();
        else if(ch==2) mft_sim();
        else break;
    }
    return 0;
}

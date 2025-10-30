/*
Simulates three file-allocation strategies on a simple disk of fixed blocks:
1) Sequential (contiguous): file occupies consecutive blocks.
2) Indexed: index block stores list of data block numbers.
3) Linked: each block stores pointer to next block (we simulate pointers as indices).
This program lets user allocate files and view allocation table.
*/

#include <stdio.h>
#include <string.h>
#define DISK_BLOCKS 50
#define MAX_FILES 20

int disk[DISK_BLOCKS];

void init() { for(int i=0;i<DISK_BLOCKS;i++) disk[i]=0; }

void show_disk(){
    printf("\nDisk Blocks (0=free, 1=used):\n");
    for(int i=0;i<DISK_BLOCKS;i++){
        printf("%2d ", disk[i]);
        if((i+1)%10==0) printf("\n");
    }
    printf("\n");
}

/* Sequential allocation: try to find `size` contiguous free blocks */
int sequential_alloc(int size){
    for(int i=0;i<=DISK_BLOCKS-size;i++){
        int ok=1;
        for(int j=0;j<size;j++) if(disk[i+j]) { ok=0; break;}
        if(ok){
            for(int j=0;j<size;j++) disk[i+j]=1;
            return i; /* starting block */
        }
    }
    return -1;
}

/* Indexed allocation: find one free index block and `size` other blocks */
int indexed_alloc(int size, int indexList[]){
    int idx=-1;
    for(int i=0;i<DISK_BLOCKS;i++) if(!disk[i]){ idx=i; break; }
    if(idx==-1) return -1;
    disk[idx]=1; /* reserve index block */
    int cnt=0;
    for(int i=0;i<DISK_BLOCKS && cnt<size;i++){
        if(!disk[i] && i!=idx){ disk[i]=1; indexList[cnt++]=i; }
    }
    if(cnt<size){ /* rollback */
        disk[idx]=0;
        for(int j=0;j<cnt;j++) disk[indexList[j]]=0;
        return -1;
    }
    return idx;
}

/* Linked allocation: allocate `size` blocks and return head index; store "next" in an array */
int linked_alloc(int size, int next[]){
    int cnt=0, head=-1, prev=-1;
    for(int i=0;i<DISK_BLOCKS && cnt<size;i++){
        if(!disk[i]){
            disk[i]=1;
            if(head==-1) head=i;
            if(prev!=-1) next[prev]=i;
            prev=i;
            cnt++;
        }
    }
    if(cnt<size){ /* rollback */
        int cur=head;
        while(cur!=-1){
            int nxt=next[cur];
            disk[cur]=0;
            next[cur]=-1;
            cur=nxt;
        }
        return -1;
    }
    next[prev] = -1; /* end */
    return head;
}

int main(){
    init();
    int choice;
    while(1){
        printf("\n1.Show disk  2.Sequential alloc  3.Indexed alloc  4.Linked alloc  5.Exit\nChoice: ");
        if(scanf("%d",&choice)!=1) return 0;
        if(choice==1) show_disk();
        else if(choice==2){
            int size; printf("Enter file size (blocks): "); scanf("%d",&size);
            int start = sequential_alloc(size);
            if(start==-1) printf("Cannot allocate sequentially.\n");
            else printf("Allocated from block %d to %d\n", start, start+size-1);
        } else if(choice==3){
            int size; printf("Enter file size (blocks): "); scanf("%d",&size);
            int idxList[DISK_BLOCKS]; for(int i=0;i<DISK_BLOCKS;i++) idxList[i]=-1;
            int idx = indexed_alloc(size, idxList);
            if(idx==-1) printf("Indexed allocation failed.\n");
            else{
                printf("Index block at %d. Data blocks:", idx);
                for(int i=0;i<size;i++) printf(" %d", idxList[i]);
                printf("\n");
            }
        } else if(choice==4){
            int size; printf("Enter file size (blocks): "); scanf("%d",&size);
            int next[DISK_BLOCKS]; for(int i=0;i<DISK_BLOCKS;i++) next[i]=-1;
            int head = linked_alloc(size, next);
            if(head==-1) printf("Linked allocation failed.\n");
            else{
                printf("Linked list head at %d. Chain: ", head);
                int cur=head;
                while(cur!=-1){ printf("%d ", cur); cur = next[cur]; }
                printf("\n");
            }
        } else break;
    }
    return 0;
}

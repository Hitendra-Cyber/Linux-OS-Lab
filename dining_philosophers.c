/*
===============================================================================
The Dining Philosophers problem illustrates synchronization among processes
competing for limited shared resources (chopsticks). Each philosopher alternates
between thinking and eating, but can eat only when both left and right chopsticks
are available.

Here:
- We use integers to represent chopsticks (0 = available, 1 = taken).
- No threads are used; actions are simulated via menu-driven input.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

int state[5];      // 0 = thinking, 1 = hungry, 2 = eating
int chopstick[5];  // 0 = available, 1 = taken

void test(int phnum) {
    if (state[phnum] == 1 && 
        chopstick[phnum] == 0 && 
        chopstick[(phnum + 1) % 5] == 0) {
        state[phnum] = 2;
        chopstick[phnum] = chopstick[(phnum + 1) % 5] = 1;
        printf("Philosopher %d is eating.\n", phnum + 1);
    } else {
        printf("Philosopher %d cannot eat now.\n", phnum + 1);
    }
}

void putdown(int phnum) {
    if (state[phnum] == 2) {
        state[phnum] = 0;
        chopstick[phnum] = chopstick[(phnum + 1) % 5] = 0;
        printf("Philosopher %d puts down chopsticks and starts thinking.\n", phnum + 1);
    } else {
        printf("Philosopher %d is not eating currently.\n", phnum + 1);
    }
}

int main() {
    int i, choice, phnum;

    for (i = 0; i < 5; i++) {
        state[i] = 0;
        chopstick[i] = 0;
    }

    printf("Dining Philosophers Problem Simulation (Without pthreads)\n");

    while (1) {
        printf("\n1. Try to Eat\n2. Putdown Chopsticks\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter philosopher number (1-5): ");
                scanf("%d", &phnum);
                phnum--;
                state[phnum] = 1;
                test(phnum);
                break;
            case 2:
                printf("Enter philosopher number (1-5): ");
                scanf("%d", &phnum);
                phnum--;
                putdown(phnum);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

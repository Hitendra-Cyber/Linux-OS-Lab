/*
===============================================================================
The Producer-Consumer problem is a classic synchronization problem.
Here, a producer creates items and puts them into a buffer, while a consumer
takes items out of it. To avoid race conditions, semaphores are used to
synchronize access to the shared buffer.

In this simulation:
- We use integer semaphores (mutex, full, empty) to control access.
- No actual threads — simulation done using menu-driven approach.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 3; // buffer size
int x = 0;     // item counter

void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer() {
    wait(&mutex);
    wait(&empty);
    signal(&full);
    x++;
    printf("Producer produces item %d\n", x);
    signal(&mutex);
}

void consumer() {
    wait(&mutex);
    wait(&full);
    signal(&empty);
    printf("Consumer consumes item %d\n", x);
    x--;
    signal(&mutex);
}

int main() {
    int n;
    printf("\nProducer-Consumer Problem Simulation\n");
    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                if ((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("Buffer is full!\n");
                break;
            case 2:
                if ((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("Buffer is empty!\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

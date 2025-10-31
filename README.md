# Linux OS Lab

This repository contains C programs that simulate various **Operating System concepts** as part of the Linux OS Lab.

---

## Overview
Each program demonstrates a specific OS concept such as process scheduling, memory management, file allocation, disk scheduling, and process synchronization (IPC).

---

## Programs Included
1. **CPU Scheduling Algorithms** – FCFS, SJF, Round Robin, Priority  
2. **File Allocation Strategies** – Sequential, Indexed, Linked  
3. **Multi-Level Queue Scheduling** – System and User processes  
4. **Memory Management** – MVT and MFT simulation  
5. **Contiguous Memory Allocation** – Worst-fit, Best-fit, First-fit  
6. **Banker's Algorithm** – Deadlock avoidance  
7. **Disk Scheduling** – FCFS, SSTF  
8. **Producer-Consumer Problem** – Using semaphores (without pthreads)  
9. **Dining Philosophers Problem** – Simulated without pthreads  

---

## How to Compile & Run
Use the GCC compiler in your Linux terminal:

```bash
gcc filename.c -o output
./output

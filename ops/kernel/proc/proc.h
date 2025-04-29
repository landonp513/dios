#ifndef __PROC_H
#define __PROC_H

typedef struct PCB {
    int pid;
    int state
    void* stkptr;
    struct PCB* next;
} PCB;

void init_proc();
void sched();

#endif
/* #ifndef __PROC_H
#define __PROC_H

typedef struct PCB {
    int pid;
    int state;
    int priority;
    int counter;
    void* stkptr;
    struct PCB* next;
    int burstime;
    int memorylim;
} PCB;

void init_proc();
void sched();

#endif */
#ifndef TCB_H
#define TCB_H

struct TCB
{
    void (*taskFunction)(void*);
    void* dataPtr;
 
};
typedef struct TCB task;

task mTCB;
task wTCB;
//task sTCB;

void TCBMain();


#endif

#ifndef scheduler
#define scheduler

struct Q {
    task* head;
    task* tail;    
};
typedef struct Q taskQueue;

void initQueue(taskQueue queue); 

void insert(task* node, taskQueue queue);

void remove(task* node, taskQueue queue);

#endif

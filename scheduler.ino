#include "TCB.h"
#include "schedule.h"

void initQueue(taskQueue queue) {
    queue -> head = NULL;
    queue -> tail = NULL;
}

void insert(task* node, taskQueue* queue){
  if(NULL == head) 
    {
      queue -> head = node; 
      queue -> tail = node;
    }
  else 
    {
      queue -> tail -> next = node;
      queue -> node -> prev = queue -> tail;
      queue -> tail = node; 
    }
  return; 
}

void remove(task* node, taskQueue* queue){
  if(NULL == head){
    
  }
  else if (queue -> head == queue -> tail && queue -> head == node){
    queue -> head = NULL;
    queue -> tail = NULL;
  }
  else if (queue -> head == node){
    temp = queue -> head -> next;
    queue -> head -> next = NULL;
    queue -> head = temp;  
  }

  else if (tail == node){
    temp = queue -> tail -> prev;
    queue -> tail -> prev = NULL;
    queue -> tail = temp;
  }

  else{
    temp = queue -> head;
    while(NULL != temp){
      if(temp == node){
        tempprev = temp -> prev;
        tempnext = temp -> next;
        tempprev -> next = tempnext;
        tempnext -> prev = tempprev;
        temp -> next = NULL;
        temp -> prev = NULL;
        temp = NULL;
      }
      else{
        temp = temp -> next;
      }
    }
    
  } 
}

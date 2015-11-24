/*
* Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
*
* Copyright (C) 2015, <GROUP MEMBERS>
* All rights reserved.
*
*/
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define

// Put global environment variables here


// Define functions declared in hostd.h here

int main(int argc, char *argv[])
{
  //Init queues
  q_dispatch = (queue*)malloc(sizeof(queue*));
  q_dispatch->head=NULL;
  q_dispatch->tail=NULL;

  q_real = (queue*)malloc(sizeof(queue*));
  q_real->head=NULL;
  q_real->tail=NULL;

  q_1 = (queue*)malloc(sizeof(queue*));
  q_1->head=NULL;
  q_1->tail=NULL;

  q_2 = (queue*)malloc(sizeof(queue*));
  q_2->head=NULL;
  q_2->tail=NULL;

  q_3 = (queue*)malloc(sizeof(queue*));
  q_3->head=NULL;
  q_3->tail=NULL;

  //Init resources
  for(int i=0;i<PRINTERS;i++){res_avail.printers[i]=0;}
  for(int i=0;i<SCANNERS;i++){res_avail.scanners[i]=0;}
  for(int i=0;i<MODEMS;i++){res_avail.modems[i]=0;}
  for(int i=0;i<DRIVES;i++){res_avail.drives[i]=0;}
  for(int i=0;i<MEMORY;i++){res_avail.memory[i]=0;}

  // Load the dispatchlist adds to queue as well
  load_dispatch("dispatchlist");

  int tick =0;
  //Start dispatching
  while(true){
    printf("Tick: %d\n",tick);
    //check dispatch list for processes that have arrived
    node* dispatch_node = q_dispatch->head;
    while(dispatch_node){
      if(dispatch_node->process.arrival_time==tick){
        //Push process to appropriate queue
        switch(dispatch_node->process.priority){
          case 0:
          push(q_real,dispatch_node->process);
          break;
          case 1:
          push(q_1,dispatch_node->process);
          break;
          case 2:
          push(q_2,dispatch_node->process);
          break;
          case 3:
          push(q_3,dispatch_node->process);
          break;
        }
      }
      dispatch_node=dispatch_node->next;
    }

    //Run processes
    proc* real;
    if(real = pop(q_real)){
      run_proc(real,1);
    }else{

    }

    tick++;
    if(tick>20){break;}
  }



  // Allocate the resources for each process before it's executed

  // Execute the process binary using fork and exec

  // Perform the appropriate signal handling / resource allocation and de-alloaction

  // Repeat until all processes have been executed, all queues are empty

  return EXIT_SUCCESS;
}

/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdbool.h>

#define MEMORY 1024
#define PRINTERS 2
#define SCANNERS 1
#define MODEMS 1
#define DRIVES 2

typedef struct{
  int printers[PRINTERS];
  int scanners[SCANNERS];
  int modems[MODEMS];
  int drives[DRIVES];
  int memory[MEMORY];
}resources;

typedef struct{
  int arrival_time;
  int priority;
  int runtime;
  int memory;
  int printers;
  int scanners;
  int modems;
  int drives;

  int pid;
  int address;
  bool suspended;
}proc;

// Include your relevant functions declarations here they must start with the
// extern keyword such as in the following examples:

extern int run_proc(proc* process,int real_time);

// Function to allocate a contiguous chunk of memory in your resources structure
// memory array, always make sure you leave the last 64 values (64 MB) free, should
// return the index where the memory was allocated at
// extern int alloc_mem(resources res, int size);

// Function to free the allocated contiguous chunk of memory in your resources
// structure memory array, should take the resource struct, start index, and
// size (amount of memory allocated) as arguments
// extern free_mem(resources res, int index, int size);

// Function to parse the file and initialize each process structure and add
// it to your job dispatch list queue (linked list)
// extern void load_dispatch(char *dispatch_file, node_t *queue);


#endif /* UTILITY_H_ */

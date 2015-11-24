/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef HOSTD_H_
#define HOSTD_H_

#include "queue.h"
#include "utility.h"

queue* q_dispatch;

queue* q_real;
queue* q_1;
queue* q_2;
queue* q_3;
resources res_avail;

// Include any relevant functions declarations here they must start with the
// extern keyword such as in the following example:
// extern void print_process(proc process);
 extern void load_file(int* rq[10][8]);

#endif /* HOSTD_H_ */

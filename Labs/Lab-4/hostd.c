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
#define MEMORY 1024
#define MAX_LEN 256
int* proc_inf[10][8];

// Put global environment variables here

// Define functions declared in hostd.h here
void load_file(int* rq[10][8])
{
    //Open file and ready for reading
    FILE *f;
    f = fopen("dispatchlist","r");
    char line[MAX_LEN];

    //Read in the resource requirements
    for (int i = 0; i < 10; i++){
        fgets(line,MAX_LEN,f);
        // Temporary solution for until after I get the rest of the stuff working
        sscanf(line, "%d, %d, %d, %d, %d, %d, %d, %d", &rq[i][0],&rq[i][1],&rq[i][2],&rq[i][3],&rq[i][4],&rq[i][5],&rq[i][6],&rq[i][7],&rq[i][8]);
    }
}

proc create_proc(int i){
    proc ret = new proc();
    //unfinished
}


int main(int argc, char *argv[])
{
    int printers = 2;
    int scanner = 1;
    int modem = 1;
    int cd = 2;
    int mem = MEMORY;

    load_file(proc_inf);

    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 9; j++){
            printf("%d ", proc_inf[i][j]);
        }
        printf("\n");
    }

    queue rt;
    queue p1, p2, p3;

    for(int time = 0; time < 10; time++){
        for (int i = 0; i < 10; i++){
            
            if (proc_inf[i][0] == time){

                proc item = create_proc(i);

                if(proc_inf[i][1] == 0){
                    push(rt,item);
                } else if (proc_inf[i][1] == 1){
                    push(p1,item);
                } else if (proc_inf[i][1] == 2) {
                    push(p2,item);
                } else if (proc_inf[i][1] == 3){
                    push(p3,item);
                }


            }
        }
    }


    // ==================== YOUR CODE HERE ==================== //
    
    // Add each process structure instance to the job dispatch list queue

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return 0;
}

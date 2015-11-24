/*
* Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
*
* Copyright (C) 2015, <GROUP MEMBERS>
* All rights reserved.
*
*/
#define _POSIX_SOURCE

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utility.h"
#include "hostd.h"

// Define your utility functions here, you will likely need to add more...

int alloc_mem(resources res, int size){
  int loc=0;
  _Bool ok = 1;
  while(loc<MEMORY){
    ok=1;
    if(loc+size>MEMORY){ return 0;}
    for(int i=loc;i<loc+size;i++){
      if(res.memory[i]==1){
        ok=0;
        loc=i;
        break;
      }
    }
    if(ok){
      for(int x=loc;x<loc+size;x++){
        res.memory[x]=1;
      }
      return loc;
    }else{
      for(int j=loc;j<MEMORY;j++){
        if(res.memory[j]==0){
          loc=j;
          break;
        }else if(j==MEMORY-1){
          return -1;
        }
      }
    }
  }
  return -1;
}

void free_mem(resources res,int address,int size){
  for(int i=address;i<address+size;i++){
    res.memory[i]=0;
  }
}

void load_dispatch(char *dispatch_file){
  //Open file aznd ready for reading
  FILE *f;
  f = fopen("dispatchlist","r");
  char line[1024];
  const char* s = ", ";
  char *token;

  int t_data[8];


  //Read in CSV file
  while(fgets(line,1024,f)){

    token = strtok(line, s);

    for(int i=0;i<8;i++){
      t_data[i]=atoi(token);
      token = strtok(NULL, s);
    }

    //Create process
    proc new_proc = (proc){.arrival_time=t_data[0], .priority=t_data[1], .runtime=t_data[2], .memory=t_data[3],.printers=t_data[4], .scanners=t_data[5], .modems=t_data[6], .drives=t_data[7],.pid=0, .address=0, .suspended=false};

    push(q_dispatch,new_proc);
  }

}

int run_proc(proc* process,int real_time){
  int status;
  pid_t pid;

  if(!process->suspended && process->pid==0){
    pid=fork();
    if(pid == 0){
      execlp("./process","./process",(char*) NULL);
    }else if(pid<0){
      // fork failed to fork
      fprintf(stderr,"Fork failed.\n");
      status = -1;
    }else{
      process->pid=pid;

      /*
      printf("%s executing at PID %d with priority %d. Using %d Bytes of memory for %d second(s)\n"
      ,process->name, process->pid, process->priority, process->memory, process->runtime);
      */
      if(real_time){
        sleep(process->runtime);
        kill(pid,SIGINT);
        waitpid(process->pid,&status,WUNTRACED);
        free_mem(res_avail,process->address,process->memory);
      }else if(process->runtime>1&&process->priority>0){
        sleep(1);
        kill(pid,SIGTSTP);
        waitpid(process->pid,&status,WUNTRACED);
        process->runtime--;
        process->suspended=true;
        return 1;
      }else{
        sleep(process->runtime);
        kill(pid,SIGINT);
        waitpid(process->pid,&status,WUNTRACED);
        free_mem(res_avail,process->address,process->memory);
        return 0;
      }
    }
  }else{
    /*
    printf("%s executing at PID %d with priority %d. Using %d Bytes of memory for %d second(s)\n"
    ,process->name, process->pid, process->priority, process->memory, process->runtime);
    */

    if(process->runtime>1){
      kill(process->pid,SIGCONT);
      sleep(1);
      kill(process->pid,SIGTSTP);
      waitpid(process->pid,&status,WUNTRACED);
      process->runtime--;
      process->suspended=true;
      return 1;
    }else{
      kill(process->pid,SIGCONT);
      sleep(process->runtime);
      kill(process->pid,SIGINT);
      waitpid(process->pid,&status,WUNTRACED);
      free_mem(res_avail,process->address,process->memory);
      return 0;
    }
  }
  return 0;
}

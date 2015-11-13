#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"

#define MEMORY 1024

int avail_mem[MEMORY];
queue* priority;
queue* secondary;

int check_mem(int size){
  int free_mem=0;
  for(int i=0;i<MEMORY;i++){
    if(avail_mem[i]==0){
      free_mem++;
    }
    if(free_mem==size){
      break;
    }
  }

  if(free_mem>=size){
    for(int i=0;i<MEMORY;i++){
      if(free_mem>0){
        if(avail_mem[i]==0){
          avail_mem[i]=1;
          free_mem--;
        }
      }else{
        return 1;
      }
    }
  }else{
    return 0;
  }
}

void free_mem(int size){
  int mem=0;
  for(int i=0;i<MEMORY;i++){
    if(mem<size){
      if(avail_mem[i]==1){
        avail_mem[i]=0;
        mem++;
      }else{
        return;
      }
    }
  }
}

  void run_proc(proc* process){
    int status;
    pid_t pid;
    pid=fork();
    if(pid == 0){
      execlp("./process",(char*) NULL);
    }else if(pid<0){
      // fork failed to fork
      fprintf(stderr,"Fork failed.\n");
      status = -1;
    }else {
      process->pid=pid;
      sleep(process->runtime);
      kill(pid,SIGINT);
      waitpid(pid,&status,0);
      printf("%s executed at PID %d with priority %d.\nUsing %d Bytes of memory for %d second(s)\n",process->name,process->pid,process->priority,process->memory,process->runtime);
      free_mem(process->memory);
    }
  }

  int main(void){
    priority = (queue*)malloc(sizeof(queue*));
    priority->head=NULL;
    priority->tail=NULL;
    secondary = (queue*)malloc(sizeof(queue*));
    secondary->head=NULL;
    secondary->tail=NULL;
    for(int i=0;i<MEMORY;i++){
      avail_mem[i]=0;
    }

    //Open file aznd ready for reading
    FILE *f;
    f = fopen("processes_q5.txt","r");
    char line[1024];
    const char* s=", ";
    char *token;

    char* t_name[256];
    int* t_data[4];

    //Read in CSV file
    while(fgets(line,1024,f)){

      token = strtok(line, s);

      for(int i=0;i<4;i++)
      {
        if(i==0)
        {
          strcpy(t_name,token);
        } else {
          token = strtok(NULL, s);
          t_data[i]=atoi(token);
        }
      }

      //Create process
      proc new_proc = (proc){.name="",.priority=t_data[1],.pid=0,.address=0,.memory=t_data[2],.runtime=t_data[3]};
      strcpy(new_proc.name,t_name);
      printf("Creating Process Priority: %d using %d mem\n",new_proc.priority,new_proc.memory);
      if(new_proc.priority==0){
        push(priority,new_proc);
      }else{
        push(secondary,new_proc);
      }

    }

    //Pop priority
    proc* pri_proc = pop(priority);
    while(pri_proc){
      if(check_mem(pri_proc->memory)){
        printf("Good");
        run_proc(pri_proc);
      }else{
        //  printf("Bad");
        push(priority,*pri_proc);
      }
      pri_proc = pop(priority);
    }

    //Pop secondary
    proc* sec_proc = pop(secondary);
    while(sec_proc){
      if(check_mem(sec_proc->memory)){
        run_proc(sec_proc);
      }else{
        printf("Pushing: %d\n",sec_proc->memory);
        push(secondary,*sec_proc);
      }
      sec_proc = pop(secondary);
    }

  }

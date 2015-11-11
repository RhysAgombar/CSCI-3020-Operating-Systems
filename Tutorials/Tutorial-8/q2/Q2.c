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

int main(void){
  priority = (queue*)malloc(sizeof(queue*));
  secondary = (queue*)malloc(sizeof(queue*));
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

    for(int i=0;i<3;i++)
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
    printf("Creating Process Priority: %d\n",new_proc.priority);
    if(new_proc.priority==0){
      push(priority,new_proc);
    }else{
      push(secondary,new_proc);
    }

  }

  

}

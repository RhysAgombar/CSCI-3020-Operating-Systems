#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "bintree.h"

#define MAX 1024

node* curr;
node* base;

int main(){
  curr = (node*)malloc(sizeof(node));
  base = (node*)malloc(sizeof(node));
  base->left = NULL;
  base->right = NULL;


  proc baseproc;
  strcpy(baseproc.name,"NULL"); // initialize
  strcpy(baseproc.parent,"ignore"); // initialize
  baseproc.priority=0;
  baseproc.memory=0;

  base->process = baseproc;

  FILE* fl;
  fl = fopen("processes_tree.txt","r");
  char reader[MAX];
  const char* s = ", ";
  char *token;

  char parent[256];
  char name[256];
  char intbuff[256];
  int priority;
  int memory;

  while(fgets(reader,MAX,fl)){
    token = strtok(reader,s);
    for(int i = 0;i<4;i++){
        if(i == 0){ // parent
          strcpy(parent,token);
        }else if(i==1){ // name
          strcpy(name,token);
        }else if(i==2){ // prority
          strcpy(intbuff,token);
          priority = atoi(intbuff);
        }else if(i==3){ // memory
          strcpy(intbuff,token);
          memory = atoi(intbuff);
      }
      token = strtok(NULL,s);
    }

    proc newproc = (proc){.parent="",.name="",.priority=priority,.memory=memory};
    strcpy(newproc.parent,parent);
    strcpy(newproc.name,name);

    curr->process = newproc;

    adder(base,curr);
    //refresh();
  }

  //fclose(fl);

  //print_tree(base);

  //decon(base);

  return 0;
}

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "bintree.h"

#define MAX 256

int main(){
  bintree* bt = (bintree*)malloc(sizeof(bintree));
  bt->head = NULL;
  node_t* base = (node_t*)malloc(sizeof(node_t));
  base->left = NULL;
  base->right = NULL;
  proc* baseproc = (proc*)malloc(sizeof(baseproc));
  strcpy(baseproc->name,"NULL"); // initialize
  strcpy(baseproc->parent,"ignore"); // initialize
  baseproc->priority=0;
  baseproc->memory=0;
  base->process = *baseproc;
  bt->head = base;

  proc* newproc = NULL;

  FILE* fl = fopen("processes_tree.txt","r");
  char reader[MAX] = {0};
  const char s[3] = ", ";
  char *token;

  char parent[MAX] = {0};
  char name[MAX] = {0};
  char intbuff[MAX] = {0};
  int priority = 0;
  int memory = 0;

  while(fgets(reader,MAX,fl)!=NULL){
    memset(&parent[0],0,sizeof(parent));
    memset(&name[0],0,sizeof(name));
    memset(&intbuff[0],0,sizeof(intbuff));
    priority = 0;
    memory = 0;

    token = strtok(reader,s);
    for(int i = 0;i<4;i++){
      if(token!=NULL){
        size_t ln = strlen(token)-1;
        if(token[ln]=='\n')
        token[ln] = '\0';
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
      }
      token = strtok(NULL,s);
    }

    newproc = (proc*)malloc(sizeof(newproc));
    strcpy(newproc->parent,parent);
    strcpy(newproc->name,name);
    newproc->priority = priority;
    newproc->memory = memory;
    printf("%s %s %d %d\n",newproc->parent,newproc->name,newproc->priority,newproc->memory);
    add_node(bt->head,newproc);
  }

  fclose(fl);

  print_tree(bt->head);

  decon(bt->head);

  return 0;
}

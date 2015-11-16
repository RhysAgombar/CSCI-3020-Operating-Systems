#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "bintree.h"

_Bool added = 0;
_Bool exist = 0;

// define functions here

void dfs(node_t* tree,char parent[256]){
  if(strcmp(tree->process.name,parent)==0){
    exist = 1;
  }else{
    if(tree->left!=NULL)
    dfs(tree->left,parent);
    else if (tree->right!=NULL)
    dfs(tree->right,parent);
  }
}

void add_node(node_t* tree, proc* process){
  // function is split into two so that the added flag can work right
  added = 0;
  //exist = 0;
  //dfs(tree,process->name);
  create_node(tree,process);
}

void create_node(node_t* tree,proc* process){

  if(tree!=NULL && added == 0){
    char partemp[256] = {0};
    char currtemp[256] = {0};
    strcpy(partemp,process->parent);
    strcpy(currtemp,tree->process.name);

    if(strcmp(currtemp,partemp)!=0){

      if(tree->left!=NULL){
        create_node(tree->left,process);
      }else if(tree->right!=NULL){
        create_node(tree->right,process);
      }else if(!added){
        node_t* newnode = (node_t*)malloc(sizeof(node_t));
        newnode->process = *process;
        newnode->left = NULL;
        newnode->right = NULL;

        if(tree->left==NULL)
        tree->left = newnode;
        else if(tree->right==NULL)
        tree->right = newnode;
        printf("add\n");
        added = 1;
      }

    }else if (strcmp(currtemp,partemp)==0){
      if(tree->left==NULL){
        // create a new node on the left and set the current node's left to it
        node_t* newnode = (node_t*)malloc(sizeof(node_t));
        newnode->process = *process;
        newnode->left = NULL;
        newnode->right = NULL;
        if(tree->left==NULL){
          tree->left = newnode;
        }else if(tree->right==NULL){
          tree->right = newnode;
        }
        printf("add \n");
        added = 1; // we have added something, sotp adding
      }
    }
  }
}

void decon(node_t* tree){
  if(tree != NULL){
    decon(tree->left);
    decon(tree->right);
    free(tree);
  }
}

void print_tree(node_t* tree){

  if(tree!=NULL){
    if(tree->left!=NULL){
      fprintf(stdout,"%s left:--> %s\n",tree->process.name,tree->left->process.name);
    }
    if(tree->right!=NULL){
      fprintf(stdout,"%s right:--> %s\n",tree->process.name,tree->right->process.name);
    }
    print_tree(tree->left);
    print_tree(tree->right);
  }
}

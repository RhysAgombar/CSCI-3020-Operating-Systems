#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "bintree.h"

_Bool added = 0;

// define functions here

void dfs(node_t* tree){
  if(tree->left!=NULL)
  dfs(tree->left);
  else if (tree->right!=NULL)
  dfs(tree->right);
}

void add_node(node_t* tree, proc* process){
  // function is split into two so that the added flag can work right
  added = 0;
  create_node(tree,process);
}

void create_node(node_t* tree,proc* process){
    // check if there is anything on the left, if there isn't make something there
    if(tree->left == NULL){
      // create a new node on the left and set the current node's left to it
      if(!added){
      node_t* left = (node_t*)malloc(sizeof(node_t));
      left->process = *process;
      left->left = NULL;
      left->right = NULL;
      tree->left = left;
      fprintf(stdout,"new node created on left \n"); // debug
      added = 1; // we have added something, sotp adding
    }
    }
    // otherwise make the new node on the right
    else if(tree->right == NULL){
      // ditto on the right
      if(!added){
      node_t* right = (node_t*)malloc(sizeof(node_t));
      right->process = *process;
      right->left = NULL;
      right->right = NULL;
      tree->right = right;
      fprintf(stdout,"new node created on right \n");
      added = 1;
    }
    }
    // if there is stuff, keep iterating through
    else{
      if(tree->left!=NULL)
      create_node(tree->left,process);
      if(tree->right!=NULL)
      create_node(tree->right,process);
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
      fprintf(stdout,"%s --> %s\n",tree->process.name,tree->left->process.name);
    }
    if(tree->right!=NULL){
      fprintf(stdout,"%s --> %s\n",tree->process.name,tree->right->process.name);
    }
    print_tree(tree->left);
    print_tree(tree->right);
  }
}

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
  added = 0;
  create_node(tree,process);
}

void create_node(node_t* tree,proc* process){

  // if(tree->left == NULL && added == 0){
  //   node_t* newnode = (node_t*)malloc(sizeof(node_t));
  //   newnode->process = *process;
  //   newnode->left = NULL;
  //   newnode->right = NULL;
  //   tree->left = newnode;
  //   added = 1;
  // }else if(tree->right == NULL && added == 0){
  //   node_t* newnode = (node_t*)malloc(sizeof(node_t));
  //   newnode->process = *process;
  //   newnode->left = NULL;
  //   newnode->right = NULL;
  //   tree->right = newnode;
  //   added = 1;
  // }else{
  //   create_node(tree->left,process);
  //   create_node(tree->right,process);
  // }
  if(tree->left == NULL && added == 0){
    node_t* left = (node_t*)malloc(sizeof(node_t));
    left->process = *process;
    left->left = NULL;
    left->right = NULL;
    tree->left = left;
    fprintf(stdout,"new node created on left \n");
    added = 1;
  }else if(tree->right == NULL && added == 0){
    node_t* right = (node_t*)malloc(sizeof(node_t));
    right->process = *process;
    right->left = NULL;
    right->right = NULL;
    tree->right = right;
    fprintf(stdout,"new node created on right \n");
    added = 1;
  }
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
  if(tree->left!=NULL){
    fprintf(stdout,"%s --> %s\n",tree->process.name,tree->left->process.name);
    print_tree(tree->left);
  }
  if(tree->right!=NULL){
    fprintf(stdout,"%s --> %s\n",tree->process.name,tree->right->process.name);
    print_tree(tree->right);
  }
}

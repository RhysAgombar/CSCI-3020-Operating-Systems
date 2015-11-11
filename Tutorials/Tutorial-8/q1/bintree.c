#include "bintree.h"

_Bool added = 0;

// define functions here

void dfs(node_t* tree){
  if(tree->left!=NULL)
  dfs(tree->left);
  else if (tree->right!=NULL)
  dfs(tree->right);
}

void add_node(node_t* tree,proc* process){

  if(!added){
    if(tree->left!=NULL){
      add_node(tree->left,process);
    }
    else{
      node_t* left = (node_t*)malloc(sizeof(node_t));
      left->process = *process;
      tree->left = left;
      added = 1;
    }
    if (tree->right!=NULL){
      add_node(tree->right,process);
    }else{
      node_t* right = (node_t*)malloc(sizeof(node_t));
      right->process = *process;
      tree->right = right;
      added = 1;
    }
  }
}

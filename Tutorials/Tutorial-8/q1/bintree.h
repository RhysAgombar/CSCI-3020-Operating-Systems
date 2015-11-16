#include <stdlib.h>

typedef struct{
  char parent[256];
  char name[256];
  int priority;
  int memory;
}proc;

typedef struct node{
  proc process;
  struct node* left;
  struct node* right;
}node_t;

// functions
extern void dfs(node_t* tree,char parent[256]); // depth first search
extern void adder(node_t**,node_t* process); // initialize adding new node
extern void refresh(); // set flags back
extern void decon(node_t* tree); // delete the entire tree
extern void print_tree(node_t* tree); // print the tree to screen

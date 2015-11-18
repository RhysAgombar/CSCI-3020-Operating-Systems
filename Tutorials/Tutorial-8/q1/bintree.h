#include <stdlib.h>

typedef struct{
  char parent[256];
  char name[256];
  int priority;
  int memory;
}proc;

typedef struct node_{
  proc process;
  struct node_* left;
  struct node_* right;
}node;

// functions
extern void dfs(node* tree,char parent[256]); // depth first search
extern void adder(node**,node* process); // initialize adding new node
extern void refresh(); // set flags back
extern void decon(node* tree); // delete the entire tree
extern void print_tree(node* tree); // print the tree to screen

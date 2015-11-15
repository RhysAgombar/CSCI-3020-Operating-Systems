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

typedef struct{
  node_t* head;
  node_t* last_left;
  node_t* last_right;
}bintree;

// functions
extern void dfs(node_t* tree); // depth first search
extern void add_node(node_t*,proc* process); // initialize adding new node
extern void create_node(node_t* tree,proc* process); // add a node to the tree
extern void decon(node_t* tree); // delete the entire tree
extern void print_tree(node_t* tree); // print the tree to screen

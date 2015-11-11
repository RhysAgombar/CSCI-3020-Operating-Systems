#include <stdlib.h>

typedef struct{
  char parent[256];
  char child[256];
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
extern void dfs(node_t* tree);
extern void add_node(node_t* tree,proc* process);

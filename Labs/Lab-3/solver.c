#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "utility.h"

int** Garr;

void load(int* arr[9][9]){
  FILE *f;
  f = fopen("puzzle.txt","r");

  for (int y = 0; y < 9; y++){
    for (int x = 0; x < 9; x++){
      fscanf(f,"%d",&arr[x][y]);
    }
  }

}

int* allocate_mem(int*** arr, int n, int m){
  *arr = (int**)malloc(n * sizeof(int*));
  int *arr_data = malloc(n*m*sizeof(int));
  for(int i = 0; i < n; i++){
    (*arr)[i] = arr_data + i * m;
  }
  return arr_data;
}

void deallocate_mem(int*** arr, int* arr_data){
  free(arr_data);
  free(*arr);
}

int main (int argc, char *argv[]){

  allocate_mem(&Garr,9,9);

  load(&Garr);

  for (int y = 0; y < 9; y++){
    for (int x = 0; x < 9; x++){
      printf("before");
      printf("%d ",Garr[x][y]);
      printf("after");
    }
    printf("\n");
  }

  return 0;
}

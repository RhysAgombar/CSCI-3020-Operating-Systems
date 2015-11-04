#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <pthread.h>

int* sudoku_board[9][9];
_Bool* sudoku_solution[9][9][10];

pthread_t t_col;
pthread_t t_row;
pthread_t t_box;



void load(int* arr[][9]){
  FILE *f;
  f = fopen("puzzle.txt","r");

  for(int y=0;y<9;y++){
    for(int x=0;x<9;x++){
      arr[x][y]=0;
    }
  }

  for (int y = 0; y < 9; y++){
    for (int x = 0; x < 9; x++){
      fscanf(f,"%d",&arr[x][y]);
    }
  }

  for (int y = 0; y < 9; y++){
    for (int x = 0; x < 9; x++){
      int index=arr[x][y];
      if(index!=0){
        sudoku_solution[x][y][index]=1;
      }else{
        for(int z=0;z<10;z++){
          sudoku_solution[x][y][z]=1;
        }
      }
    }
  }
}

void check_pos(){
  
}

int main (int argc, char *argv[]){

  load(&sudoku_board);

  printf("-----\n");

  for (int j = 0; j < 9; j++){
    for (int k = 0; k < 9; k++){
      printf("%d ",sudoku_board[k][j]);
    }
    printf("\n");
  }
  return 0;
}

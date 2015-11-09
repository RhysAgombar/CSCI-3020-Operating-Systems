#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
  int x;
  int y;
}vector;

pthread_t t_col;
pthread_t t_row;
pthread_t t_box;

pthread_mutex_t mutex;

int* sudoku_board[9][9];
_Bool* sudoku_solution[9][9][10];

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
  fclose(f);
}


void* check_row(void* arg){
  vector* pos = arg;
  int xx=pos->x;
  int yy=pos->y;

  for(int x=0;x<9;x++){
    pthread_mutex_lock(&mutex);
    int position = sudoku_board[x][yy];
    if(position){
      //printf("Row Found: %d\n",position);
    }
    sudoku_solution[xx][yy][position]=0;
    pthread_mutex_unlock(&mutex);
  }
}

void *check_col(void* arg){
  vector* pos = arg;
  int xx=pos->x;
  int yy=pos->y;
  //printf("xx=%d, yy=%d\n",xx,yy);
  for(int y=0;y<9;y++){
    pthread_mutex_lock(&mutex);
    int position = sudoku_board[xx][y];
    if(position){
      //printf("Col Found @ (%d,%d) : %d\n",xx,yy,position);
    }
    sudoku_solution[xx][yy][position]=0;
    pthread_mutex_unlock(&mutex);
  }
  //printf("Check col done\n");
}


void* check_box(void* arg){
  vector* pos = arg;
  int xx=pos->x;
  int yy=pos->y;

  int start_y=(yy / 3)*3;
  int start_x=(xx / 3)*3;
  for(int y=start_y;y<start_y+3;y++){
    for(int x=start_x;x<start_x+3;x++){
      pthread_mutex_lock(&mutex);
      int position = sudoku_board[x][y];
      if(position){
        //printf("Square Found: %d\n",position);
      }
      sudoku_solution[xx][yy][position]=0;
      pthread_mutex_unlock(&mutex);
    }
  }
}


void check_pos(int xx,int yy){
  vector* pos = (vector*)malloc(sizeof(vector*));
  pos->x=xx;
  pos->y=yy;
  pthread_create(&t_col,NULL,check_col,(void *)pos);
  pthread_create(&t_row,NULL,check_row,(void *)pos);
  pthread_create(&t_box,NULL,check_box,(void *)pos);
  pthread_join(t_row,0);
  pthread_join(t_box,0);
  pthread_join(t_col,0);
  free(pos);

  //cell has been checked
  sudoku_solution[xx][yy][0]=0;
}

int main (void){

  if (pthread_mutex_init(&mutex, NULL) != 0){
        printf("\n mutex init failed\n");
  }

  load(&sudoku_board);
  _Bool solved=0;

  for (int j = 0; j < 9; j++){
    for (int k = 0; k < 9; k++){
      printf("%d ",sudoku_board[k][j]);
    }
    printf("\n");
  }

  printf("------Original------\n");

  while(!solved){
    solved=1;
    //printf("-----\n");

    for (int j = 0; j < 9; j++){
      for (int k = 0; k < 9; k++){
        //printf("%d ",sudoku_board[k][j]);
        check_pos(k,j);
      }
      //printf("\n");
    }


    //printf("-----\n");
    for (int j = 0; j < 9; j++){
      for (int k = 0; k < 9; k++){
        if(sudoku_board[k][j]==0){
          int single=0;
          printf("Checking %d,%d: ",k,j);
          for(int l=1;l<10;l++){
            if(sudoku_solution[k][j][l]==1){
              if(single==0){
                single = l;
              }else{
                single=0;
                printf("Broke on %d\n",l);
                break;
              }
            }
          }
          if(single){
            printf("Single Found: %d\n",single);
            sudoku_board[k][j]=single;
          }
        }
        //printf("%d ",sudoku_board[k][j]);
      }
      //printf("\n");
    }

    for(int j=0;j<9;j++){
      for(int k=0;k<9;k++){
        if(sudoku_board[k][j]==0){
          solved=0;
        }
      }
    }
  }

  printf("--------Solved--------\n");

  for (int j = 0; j < 9; j++){
    for (int k = 0; k < 9; k++){
      printf("%d ",sudoku_board[k][j]);
    }
    printf("\n");
  }

  pthread_mutex_destroy(&mutex);
  return 0;
}

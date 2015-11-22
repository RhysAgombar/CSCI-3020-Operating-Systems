#include <stdio.h>
#include <omp.h>

#define matrix_size 100

int main (int argc, char *argv[])
{
  int nthreads = 16;

  #ifdef _OPENMP
  omp_set_num_threads(nthreads);
  #endif

  int a[matrix_size][matrix_size];
  int b[matrix_size][matrix_size];
  int c[matrix_size][matrix_size];

  int sum;

  #pragma omp parallel for
  for(int y=0;y<matrix_size;y++){
    for(int x=0;x<matrix_size;x++){
      a[y][x]=x;
      b[y][x]=y;
    }
  }

  #pragma omp parallel for
  for(int y=0;y<matrix_size;y++){
    for(int x=0;x<matrix_size;x++){
      int sum = 0;
      for(int z=0;z<matrix_size;z++){
        sum = sum + a[y][z] * b[z][x];
      }
      c[y][x] = sum;
    }
  }
  return 0;
}

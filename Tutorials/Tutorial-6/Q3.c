#define _XOPEN_SOURCE 600
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int* moving_sum[5];
sem_t sem;

struct numInd
{
   int num;
   int index;
} numInd;  


void *Factorial(struct numInd data)
    {
        printf("phase1\n");
        int fact = 1;
        for(int i = numInd.num; i > 0; i--){
            if(numInd.num == 0){
                break;
            }
            fact = fact * i;
        }
        printf("phase2\n");
        *moving_sum[numInd.index] = fact;
        printf("phase3\n");


        for(int i = numInd.index; i > 0; i--){
            sem_wait(&sem);
            *moving_sum[numInd.index] = *moving_sum[numInd.index] + *moving_sum[numInd.index-1];
            sem_post(&sem);
        }
        printf("phase4\n");
        printf("Thread %d:\n",numInd.index);
        printf("%d\n", *moving_sum[numInd.index]);

        return 0;
    }

int main(int argc, char *argv[]) {
    pthread_t pth[5];

    for(int i = 0; i < 5; i++){
        moving_sum[i] = (int*)malloc(sizeof(int));
        //moving_sum[i] = 0; IF I LEAVE THIS IN HERE, IT SEGFAULTS.
    }

    printf("Please input 5 numbers.\n");

    for(int i = 0; i < 5; i++){
        scanf("%d", moving_sum[i]);
    }

    sem_init(&sem, 0, 1);

    printf("Threads\n");
    for(int i = 0; i < 5; i++){
        struct numInd* test;
        printf("phase1\n");
        test->num = *moving_sum[i];
        test->index = i;

        printf("phase1\n");
        printf("Thread Create %d:\n", i);
        pthread_create(&pth[i], 0, Factorial, test);
        printf("phase1\n");
    }

    for(int i = 0; i < 5; i++){
        pthread_join(pth[i], 0);
    }

    for(int i = 0;i<5;i++){
      free(moving_sum[i]);
    }

    return 0;
}
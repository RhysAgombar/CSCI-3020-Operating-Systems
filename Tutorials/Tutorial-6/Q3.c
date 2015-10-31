#define _XOPEN_SOURCE 600
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define FIVE 5

int* moving_sum[5];
sem_t sem;

struct numInd
{
   int num;
   int index;
} numInd;  

void *Factorial(void *arg)
{
    sem_wait(&sem);
    struct numInd str;
    str = *(struct numInd*)arg;

    printf("Phase 1 - num = %d, ind = %d\n", str.num, str.index);
    
    int fact = 1;
    for(int i = str.num; i > 0; i--){
        if(str.num == 0){
            break;
        }
        fact = fact * i;
    }

    *moving_sum[str.index] = fact;

    printf("Thread %d factorial = %d\n", str.index, fact);

    sem_post(&sem);
/*
    if (str.index > 0){
        while (1==1) {
            //sem_wait(&sem);
            printf("Thread %d is waiting. \n", str.index);
            if (*moving_sum[str.index - 1] > 0){
                break;
            }
            //sem_post(&sem);
        }

        *moving_sum[str.index] = *moving_sum[str.index] + *moving_sum[str.index - 1];

        //for(int i = numInd.index; i > 0; i--){
            //sem_wait(&sem);
            //*moving_sum[numInd.index] = *moving_sum[numInd.index] + *moving_sum[numInd.index-1];
            //sem_post(&sem);
        //}
    }
    */
    //printf("%d\n", *moving_sum[numInd.index]);

    return 0;
}


int main (int argc, char *argv[]){

    pthread_t *pth[FIVE];

    sem_init(&sem, 0, 1);

    for(int i = 0; i < 5; i++){
        moving_sum[i] = (int*)malloc(sizeof(int));
        *moving_sum[i] = 0; 
    }

        printf("Please input 5 numbers.\n");

    for(int i = 0; i < 5; i++){
        scanf("%d", moving_sum[i]);
    }
    
    for(int i = 0;i<5;i++){

        struct numInd test;
        test.num = *moving_sum[i];
        test.index = i;

       // printf("Pre-Thread: num = %d, index = %d\n", test.num, test.index);

        pthread_create(&pth[i],NULL,Factorial,(void *) &test);
    }


    for(int i = 0;i<FIVE;i++){
        pthread_join(*pth[i],0);
    }

    for(int i = 0; i < 5; i++){
        pthread_join(&pth[i], 0);
    }

    // Clean up
    sem_destroy(&sem);

    for(int i = 0;i<5;i++){
      free(moving_sum[i]);
    }

    return 0;
}


/*
int main(int argc, char *argv[]) {

    pthread_t *pth[FIVE];

    for(int i = 0; i < 5; i++){
        moving_sum[i] = (int*)malloc(sizeof(int));
        *moving_sum[i] = 0; 
    }

    printf("Please input 5 numbers.\n");

    for(int i = 0; i < 5; i++){
        scanf("%d", moving_sum[i]);
    }

    // Initialize the semaphore.
    sem_init(&sem, 0, 1);

    // Create the threads

    for(int i = 0; i < 5; i++){

        struct numInd *test;
        (*test).num = *moving_sum[i];
        (*test).index = i;

        printf("Test->num : %d\n", (*test).num);
        printf("Test->index : %d\n", (*test).index);

        printf("Thread Create : %d\n", i);
        pthread_create(pth[i], NULL, Factorial, (void *) i);
        printf("Thread Created : %d\n", i);
    }

    printf("Done.\n");

    // Clean up
    sem_destroy(&sem);

    return 0;
}
*/
/*
int* moving_sum[5];
sem_t sem;

struct numInd
{
   int num;
   int index;
} numInd;  


void *Factorial(void *arg)//struct numInd data)
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
        *moving_sum[i] = 0; 
    }

    printf("Please input 5 numbers.\n");

    for(int i = 0; i < 5; i++){
        scanf("%d", moving_sum[i]);
    }

    sem_init(&sem, 0, 1);

    printf("Threads\n");
    for(int i = 0; i < 5; i++){
        struct numInd* test;
        test->num = *moving_sum[i];
        test->index = i;

        printf("phase1\n");
        printf("Thread Create %d:\n", i);
        pthread_t pth;
        pthread_create(&pth[i], 0, Factorial, (void *) test);
        printf("phase1\n");
    }

    for(int i = 0; i < 5; i++){
        pthread_join(pth[i], 0);
    }

    for(int i = 0;i<5;i++){
      free(moving_sum[i]);
    }

    return 0;
}*/
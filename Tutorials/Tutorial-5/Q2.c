
#include <stdio.h>
#include <pthread.h>

void *bellCurve(float *arg)
{
    float curved = (float)arg * 1.5;

    printf("%d\n",curved);

    return NULL;
}

/**
 * Basic example that showing threading interleaving.
 */
int main(int argc, char *argv[]) {

    // Thread object
    pthread_t pth[5];
    float* grades[5];

    printf("Please input 5 student grades. \n");

    for(int i = 0; i < 5; i++){
        grades[i] = (float*)malloc(sizeof(float)); 
        scanf("%d", grades[i]);
    }

    printf("Curved Grades:");

    for(int i = 0; i < 5; i++){
        pthread_create(&pth[i], 0, bellCurve, (void *) grades[i]);
    }
    // Create the thread.
    //pthread_create(&pth, 0, threadFunc, (void *) "Thread 1");

    // wait for our thread to finish before continuing
    for(int i = 0; i < 5; i++){
        pthread_join(pth[i], 0);
    }

    free(grades);
    free(pth);

    return 0;
}




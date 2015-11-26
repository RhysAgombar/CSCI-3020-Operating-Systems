/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 1
#define NUM_RESOURCES 3

// Put global environment variables here
// Available amount of each resource
int available[NUM_RESOURCES];
int total[NUM_RESOURCES];

// Maximum demand of each customer
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];


bool check_safety(int n_customer, int request[])
{
	return true;

}

// Define functions declared in banker.h here
bool request_res(int n_customer, int request[])
{
	bool result = false;
	int tempAvail[NUM_RESOURCES];
	
	printf("Customer %d request: %d %d %d\nAvailable: %d %d %d\n", n_customer, need[n_customer][0], need[n_customer][1], need[n_customer][2],available[0] ,available[1] ,available[2]);

	for (int i = 0; i < NUM_RESOURCES; i++){
		if (request[i] > need[n_customer][i]){
			result = false;
			break;
		} else if (request[i] > available[i]){
			result = false;
			break;
		} else {
			result = true;
			tempAvail[i] = available[i] - request[i];
		}
	}

	if (result == true){
			bool safe = check_safety(n_customer, tempAvail);

			if( safe == true){
				for (int i = 0; i < NUM_RESOURCES; i++){
					available[i] = available[i] - request[i]; // critical Section
					allocation[n_customer][i] = allocation[n_customer][i] + request[i];
					need[n_customer][i] = need[n_customer][i] - request[i];
				}
				result = true;
			} else {
				safe = false;
				result = false;
			}

		}

	printf("Customer %d request: %d %d %d\nAvailable: %d %d %d\n", n_customer, need[n_customer][0], need[n_customer][1], need[n_customer][2],available[0] ,available[1] ,available[2]);

	return result;

}

// Release resources, returns true if successful
bool release_res(int n_customer)
{

}

void procCust(int n_customer)
{
	int request[NUM_RESOURCES] = { 0 };

	for (int i = 0; i < 10; i++){ // Go through this song and dance 10 times

		for (int j = 0; j < NUM_RESOURCES; j++){ // Generate the initial needs
			int val = rand() % total[j];
			need[n_customer][j] = val;
			allocation[n_customer][j] = 0;
			maximum[n_customer][j] = val;
		}

		//printf("Customer %d request: %d %d %d\n", n_customer, need[n_customer][0], need[n_customer][1], need[n_customer][2]);
				

		while(1 == 1){
			sleep(1);

			for (int j = 0; j < NUM_RESOURCES; j++){ // Start generating the requests.
				request[j] = rand() % total[j]; // Can never request more than the max amount of resources we have
			}

			bool result = request_res(n_customer, request);	

			if(result == true){
				printf("Customer %d request accepted. Allocated resources: %d %d %d\n",  n_customer, request[0], request[1], request[2]);
			} else if (result == false){
				printf("Customer %d request denied. Requested (but denied) resources: %d %d %d\n",  n_customer, request[0], request[1], request[2]);
			}

			if(need[n_customer][0] - allocation[n_customer][0] == 0 && need[n_customer][1] - allocation[n_customer][1] == 0 && need[n_customer][2] - allocation[n_customer][2] == 0){ // This is gonna drive dan crazy I can tell.
				break;
			}

		}

		release_res(n_customer);














	}

}


int main(int argc, char *argv[])
{
	if ( argc != 4 ) { // I don't know why, but it has to be 4. Maybe the ./banker counts as an arguement?
        printf("ERROR: Please insert the values for 3 resources.\n");
    return 0;
    }
    else {

    	available[0] = atoi(argv[1]);
    	available[1] = atoi(argv[2]);
    	available[2] = atoi(argv[3]);
    	total[0] = atoi(argv[1]);
    	total[1] = atoi(argv[2]);
    	total[2] = atoi(argv[3]);

    }

    pthread_t *cust[NUM_CUSTOMERS];

    for(int i = 0;i<NUM_CUSTOMERS;i++){
        pthread_create(&cust[i],NULL,procCust,(void *) i);
    }



    for(int i = 0;i<NUM_CUSTOMERS;i++){
        pthread_join(*cust[i],0);
    }

    // Initialize the pthreads, locks, mutexes, etc.

    // Run the threads and continually loop

    // The threads will request and then release random numbers of resources

    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}

bool check_safety(int n_customer, int request[])
{
	bool finish[NUM_CUSTOMERS];
	int work[NUM_RESOURCES];
	//Initial allocation of the work
	for (int i = 0; i < NUM_RESOURCES; i++){
		work[i] = request[i];
	}

	//Initial allocation of which customers are safe
	for(int i = 0; i < NUM_CUSTOMERS; i++){
		finish[i] = false;
	}

	/*For each customer, go through all of the resources that customer needs. If the customer hasn't already been set to safe,
	and the customer's need's are lower or equal to the amount of work that needs to be done, then set the customer to safe.
	*/
	for(int i = 0; i < NUM_CUSTOMERS; i++){
		printf("%d",finish[i]);
	}
	printf("\n");
	for (int j = 0; j < NUM_CUSTOMERS; j++){
		for (int i = 0; i < NUM_RESOURCES; i++){
			if(finish[j] == false && need[n_customer][i] <= work[i]){
				work[i] = work[i] + allocation[n_customer][i];
				finish[i] = true;
			}
		}
	}
	for(int i = 0; i < NUM_CUSTOMERS; i++){
		printf("%d",finish[i]);
	}
	printf("\n");
	//Loop to check state of each customer. If the state of each customer is safe, then the system is safe from deadlock.
	bool state = true;
	for(int i = 0; i < NUM_CUSTOMERS; i++){
		if(finish[i] == false){
			state = false;
		}
	}
	//Return the safety of the state. True is a safe state, false is a non-safe state.
	//printf("Customer %d - Needs: %d %d %d - Allocated: %d %d %d - Available: %d %d %d - Work: %d %d %d - Request: %d %d %d\n", n_customer, need[n_customer][0], need[n_customer][1], need[n_customer][2], allocation[n_customer][0], allocation[n_customer][1], allocation[n_customer][2], available[0], available[1], available[2], work[0], work[1], work[2], request[0], request[1], request[2]);
	return state;
}
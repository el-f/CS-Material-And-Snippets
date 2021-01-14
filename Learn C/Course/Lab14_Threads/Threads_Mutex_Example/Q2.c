
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "Q2.h"


void Q2()
{
	pthread_t threads[NUM_THREADS_2];
	ThreadData thread_args[NUM_THREADS_2];
	int i,counter=0;
	int result_code;
	pthread_mutex_t bufLock;



	pthread_mutex_init(&bufLock,NULL);

	printf("IN MAIN: lock\n");
	pthread_mutex_lock(&bufLock);

	//create all threads one by one
	for (i = 0; i < NUM_THREADS_2; i++) {
		printf("IN MAIN: Creating thread %d.\n", i);
		thread_args[i].id = i;
		thread_args[i].pCounter = &counter;
		thread_args[i].pMutex = &bufLock;
		result_code = pthread_create(&threads[i], NULL, perform_work_sync, &thread_args[i]);
		assert(!result_code);
	}

	sleep(5);
	pthread_mutex_unlock(&bufLock);
	printf("IN MAIN: unlock\n");

	printf("IN MAIN: All threads are created.\n");

	//wait for each thread to complete
	for (i = 0; i < NUM_THREADS_2; i++) {
		result_code = pthread_join(threads[i], NULL);
		assert(!result_code);
		printf("IN MAIN: Thread %d has ended.\n", i);
	}

	printf("Counter after all is %d\n",counter);
	pthread_mutex_destroy(&bufLock);

	printf("MAIN program has ended.\n");
}


void* perform_work_sync(void *arguments){

	ThreadData data = *(ThreadData *)arguments;
	int index = data.id;
	printf("Thread %d before lock\n",index);
	pthread_mutex_lock(data.pMutex);
	(*data.pCounter)++;
	printf("Counter after thread %d work is %d\n",index,(*data.pCounter));
	pthread_mutex_unlock(data.pMutex);
	printf("Thread %d after lock\n",index);
	printf("THREAD %d: Ended.\n", index);
	return NULL;

}



/*
 * Q2.h
 *
 */

#ifndef Q2_H_
#define Q2_H_

#include <pthread.h>

#define NUM_THREADS_2 2

typedef struct {
    int id;
    int *pCounter;
    pthread_mutex_t *pMutex;
} ThreadData;


void *perform_work_sync(void *arguments);


void Q2();


#endif /* Q2_H_ */

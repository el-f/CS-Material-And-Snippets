/*
 * main.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void printMsg(char *msg);

#ifdef FIRST
int main(int argc, char** argv) {
    pthread_t thrdID;

    printf("creating a new thread\n");
    pthread_create(&thrdID, NULL, (void*)printMsg, argv[1]);
    printf("created thread %d\n", (int)thrdID);
    pthread_join(thrdID, NULL);
    pthread_exit(NULL);
    return 1;
}

void printMsg(char* msg) {
    printf("%s\n", msg);
}

#else

void printMsg(char *msg) {
    int *status = (int *) malloc(sizeof(int));
    *status = 17;
    printf("%s\n", msg);
    pthread_exit(status);
}

int main(int argc, char **argv) {
    pthread_t thrdID;
    void *pReturn;

    printf("creating a new thread\n");
    pthread_create(&thrdID, NULL, (void *) printMsg, argv[1]);
    printf("created thread %d\n", (int) thrdID);
    pthread_join(thrdID, &pReturn);
    printf("Thread %d exited with status %d\n", (int) thrdID, *(int *) pReturn);
    free(pReturn);
    pthread_exit(NULL);
    return 1;
}

#endif



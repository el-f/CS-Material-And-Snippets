#include "myProto.h"
#include <stdio.h>

void test(int *data, int n) {
    int i;
    for (i = 0;   i < n;   i++) {
        if (data[i] != i + 1) {
           printf("Wrong Calculations - Failure of the test at data[%d]\n", i);
           return;
    	}
    }
    printf("The test passed successfully\n"); 
}

#include "myProto.h"
#include <stdio.h>

// This function is a special - runs on Host and Device
double f(int index);

void test(int *data, int n, int resultTotal) {
    int i, result = 0;
    
    // Perform a sequecial calculatiion for comparison
    for (i = 0;   i < n;   i++)
        if (f(data[i]) > 0)
      		result++;
     		
    if (result != resultTotal)
       printf("Wrong Calculations\n");
    else 
       printf("The test passed successfully\n");
}

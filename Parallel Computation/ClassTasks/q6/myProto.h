#pragma once

#define PART  25000
#define HEAVY  10000

void test(int *data, int n, int resultTotal);
int computeOnGPU(int *data, int n, int *result);

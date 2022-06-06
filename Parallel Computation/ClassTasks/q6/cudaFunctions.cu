#include <cuda_runtime.h>
#include <helper_cuda.h>
#include <math.h>
#include "myProto.h"

// This function is a special - runs on Host and Device
__device__  __host__ double f(int index) {
	int j;
	double value;
	double result = 0;

	for (j = 1; j < HEAVY; j++) {
		value = (index+1)*(j%10);
		result += cos(value);
	}
	return cos(result);
}

__global__ void kernel(int *data, double *arr, int numElements) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;

    if (i < numElements)
        arr[i] = f(data[i]);
}


int computeOnGPU(int *data, int numElements, int *result) {
    // Error code to check return values for CUDA calls
    cudaError_t err = cudaSuccess;

    
    size_t size = numElements * sizeof(int);
    
    // Allocate memory on GPU to copy the data from the host
    int *d_A;
    err = cudaMalloc((void **)&d_A, size);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to allocate device memory - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Copy data from host to the GPU memory
    err = cudaMemcpy(d_A, data, size, cudaMemcpyHostToDevice);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to copy data from host to device - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Allocate memory for array of f(data[i]) on device and on host
    double *d_B;
    size = numElements * sizeof(double);
    err = cudaMalloc((void **)&d_B, size);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to allocate device memory - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    double *B = (double *) malloc(size);
    if (B == NULL) {
        fprintf(stderr, "Failed to allocate host memory\n");
        exit(EXIT_FAILURE);
    }
    
    // Launch the Kernel to calculate f(A[i])
    int threadsPerBlock = 256;
    int blocksPerGrid =(numElements + threadsPerBlock - 1) / threadsPerBlock;
    kernel<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, numElements);
    err = cudaGetLastError();
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to launch vectorAdd kernel -  %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Copy the  result from GPU to the host memory.
    err = cudaMemcpy(B, d_B, size, cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to copy result array from device to host -%s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Calculate the result
    *result = 0;
    for (int i = 0;   i < numElements;  i++)
    	if (B[i] > 0)
    		(*result)++;
    		
    // Free allocated memory 
    if (cudaFree(d_A) != cudaSuccess || cudaFree(d_B) != cudaSuccess) {
        fprintf(stderr, "Failed to free device data - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    free(B);

    return 0;
}


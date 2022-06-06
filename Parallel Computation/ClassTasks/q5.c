#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// For the CUDA runtime routines (prefixed with "cuda_")
#include <cuda_runtime.h>

#include <helper_cuda.h>
// Kernels for three cases of the exercize
__global__ void kernel_case1(int *A, int K) {
    int i = threadIdx.x;
    A[i] += K;
}

__global__ void kernel_case3(int *A, int K, int numPerThread) {
    int i, start = threadIdx.x * numPerThread, end = start + numPerThread;
    for (i = start;  i < end;   i++) 
    	A[i] += K;
}

__global__ void kernel_case4(int *A, int K, int numPerThread) {
    int i, start = (blockDim.x*blockIdx.x + threadIdx.x ) * numPerThread, 
    	end = start + numPerThread;
    for (i = start;  i < end;   i++) 
    	A[i] += K;
}
/**
 * Host main routine
 */

int main() {

    // Error code to check return values for CUDA calls
    cudaError_t err = cudaSuccess;
    
    // Allocate and initialize the host input vector A and a result B
    int N = 256; // Modify according to the case
    int size = N * sizeof(int);
    int *A = (int *)malloc(size);
    int *B = (int *)malloc(size);
    int K = 123;
    
    if (A == NULL ||B == NULL) {
        fprintf(stderr, "Failed to allocate host vectors!\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < N; ++i)
    	A[i] = rand();
        

    // Allocate the device input vector A
    int *d_A = NULL;
    err = cudaMalloc((void **)&d_A, size);

    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }


    // Copy the host input vector A in host memory to the device input vector in
    // device memory
    printf("Copy input data from the host memory to the CUDA device\n");
    err = cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to copy vector A from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }


    // Launch the Kernel
    int threadsPerBlock = 256;
    kernel_case1<<<1, threadsPerBlock>>>(d_A, K);
    	// Ideas of Block/Grid/NumbersPerThread caculation for other cases
    //kernel_case3<<<1, 1024>>>(d_A, K, 102400/1024);
    //kernel_case4<<<102400/1024/10, 1024>>>(d_A, K, 10);
    err = cudaGetLastError();
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to launch kernel_case1 (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Copy the device result vector in device memory to the host result vector
    // in host memory.
    printf("Copy output data from the CUDA device to the host memory\n");
    err = cudaMemcpy(B, d_A, size, cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to copy vector A from device to host (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Verify that the result vector is correct
    int difference = 0;
    for (int i = 0; i < N; ++i)
    	difference += abs(B[i] - A[i]);
    
    if (difference != N*K)
       fprintf(stderr, "Result verification failed\n");
    else    
    	printf("Result verification succeded\n");

    // Free device global memory
    err = cudaFree(d_A);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to free device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    } 

    // Free host memory
    free(A);
    free(B);
    
    return 0;
}


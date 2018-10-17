#include <stdio.h>

#define BLOCK_SIZE 128

__global__ void calculateWork(int* work, const unsigned long long int leftMiddle, const unsigned long long int middle, const unsigned long long int n) {
    int i = blockIdx.x * BLOCK_SIZE + threadIdx.x;

    int temp = i % n;
    int force;
    if (temp < leftMiddle) {
        force = middle - (leftMiddle - temp);
    } else if (temp == leftMiddle || temp == middle) {
        force = middle;
    } else {
        force = n - temp;
    }
    int distance = i % 10 + 1;

    work[i] = force * distance;
}

extern "C" void gpuCalculate(int* w, const unsigned long long int leftMiddle, const unsigned long long int middle, const unsigned long long int n) {
    cudaError_t mallocResult;
    int* work;

    mallocResult = cudaMalloc((void**) &work, n * sizeof(int));
    if (mallocResult != cudaSuccess) {
        fprintf(stderr, "CUDA Malloc failed, exiting...\n");
        exit(EXIT_FAILURE);
    }

    dim3 dimBlock(BLOCK_SIZE);
    unsigned long long int gridSize = n / BLOCK_SIZE;
    if (n % BLOCK_SIZE != 0) {
        gridSize += 1;
    }
    dim3 dimGrid(gridSize);

    calculateWork<<<dimGrid, dimBlock>>>(work, leftMiddle, middle, n);

    mallocResult = cudaMemcpy(w, work, n * sizeof(int), cudaMemcpyDeviceToHost);
    if (mallocResult != cudaSuccess) {
        fprintf(stderr, "CUDA Memcpy failed, exiting...\n");
        exit(EXIT_FAILURE);
    }

    mallocResult = cudaFree(work);
    if (mallocResult != cudaSuccess) {
        fprintf(stderr, "CUDA free failed, exiting...\n");
        exit(EXIT_FAILURE);
    }
}
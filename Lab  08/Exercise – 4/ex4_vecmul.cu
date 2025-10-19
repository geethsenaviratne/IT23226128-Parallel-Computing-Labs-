#include <cstdio>
#include <cstdlib>
#include <cuda_runtime.h>
#include "cuda_check.hpp"

static void fill_random_ints(int* x, size_t n) {
    for (size_t i = 0; i < n; ++i) x[i] = rand() % 100;
}

__global__ void vecMul(const int* __restrict__ A,
                       const int* __restrict__ B,
                       int* __restrict__ C,
                       int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) C[i] = A[i] * B[i];
}

int main() {
    const int N = 10'000'000;   // 10 million
    const int TPB = 512;
    const int BLOCKS = (N + TPB - 1) / TPB;
    size_t bytes = (size_t)N * sizeof(int);

    int *hA=(int*)malloc(bytes), *hB=(int*)malloc(bytes), *hC=(int*)malloc(bytes);
    if (!hA || !hB || !hC) { fprintf(stderr,"Host malloc failed\n"); return 1; }

    fill_random_ints(hA, N);
    fill_random_ints(hB, N);

    int *dA=nullptr, *dB=nullptr, *dC=nullptr;
    CUDA_CHECK(cudaMalloc((void**)&dA, bytes));
    CUDA_CHECK(cudaMalloc((void**)&dB, bytes));
    CUDA_CHECK(cudaMalloc((void**)&dC, bytes));

    CUDA_CHECK(cudaMemcpy(dA, hA, bytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(dB, hB, bytes, cudaMemcpyHostToDevice));

    vecMul<<<BLOCKS, TPB>>>(dA, dB, dC, N);
    CUDA_CHECK(cudaDeviceSynchronize());

    CUDA_CHECK(cudaMemcpy(hC, dC, bytes, cudaMemcpyDeviceToHost));

    int start = (N > 1000) ? (N - 1000) : 0;
    for (int i = start; i < N; ++i) {
        printf("%d) %d * %d = %d\n", i, hA[i], hB[i], hC[i]);
    }

    free(hA); free(hB); free(hC);
    CUDA_CHECK(cudaFree(dA));
    CUDA_CHECK(cudaFree(dB));
    CUDA_CHECK(cudaFree(dC));
    return 0;
}

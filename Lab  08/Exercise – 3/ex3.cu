#include <cstdio>
#include <cstdlib>
#include <cuda_runtime.h>
#include "cuda_check.hpp"

#define N 512

__global__ void addT(const int* a, const int* b, int* c) {
    int i = threadIdx.x;  // 0..N-1
    c[i] = a[i] + b[i];
}

static void random_ints(int* x, int n) {
    for (int i = 0; i < n; ++i) x[i] = rand() % 100;
}

int main() {
    size_t bytes = N * sizeof(int);
    int *a=(int*)malloc(bytes), *b=(int*)malloc(bytes), *c=(int*)malloc(bytes);
    int *d_a=nullptr, *d_b=nullptr, *d_c=nullptr;

    random_ints(a, N);
    random_ints(b, N);

    CUDA_CHECK(cudaMalloc((void**)&d_a, bytes));
    CUDA_CHECK(cudaMalloc((void**)&d_b, bytes));
    CUDA_CHECK(cudaMalloc((void**)&d_c, bytes));

    CUDA_CHECK(cudaMemcpy(d_a, a, bytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_b, b, bytes, cudaMemcpyHostToDevice));

    addT<<<1, N>>>(d_a, d_b, d_c);
    CUDA_CHECK(cudaDeviceSynchronize());

    CUDA_CHECK(cudaMemcpy(c, d_c, bytes, cudaMemcpyDeviceToHost));

    for (int i = 0; i < N; ++i)
        printf("%d) %d + %d = %d\n", i, a[i], b[i], c[i]);

    free(a); free(b); free(c);
    CUDA_CHECK(cudaFree(d_a));
    CUDA_CHECK(cudaFree(d_b));
    CUDA_CHECK(cudaFree(d_c));
    return 0;
}

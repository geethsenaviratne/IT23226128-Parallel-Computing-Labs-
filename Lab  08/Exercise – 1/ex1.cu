#include <cstdio>
#include <cuda_runtime.h>
#include "cuda_check.hpp"

// device kernel
__global__ void add(const int* a, const int* b, int* c) {
    *c = *a + *b;
}

int main() {
    int a = 2, b = 7, c = 0;
    int *d_a=nullptr, *d_b=nullptr, *d_c=nullptr;
    size_t sz = sizeof(int);

    CUDA_CHECK(cudaMalloc((void**)&d_a, sz));
    CUDA_CHECK(cudaMalloc((void**)&d_b, sz));
    CUDA_CHECK(cudaMalloc((void**)&d_c, sz));

    CUDA_CHECK(cudaMemcpy(d_a, &a, sz, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_b, &b, sz, cudaMemcpyHostToDevice));

    add<<<1,1>>>(d_a, d_b, d_c);
    CUDA_CHECK(cudaDeviceSynchronize());

    CUDA_CHECK(cudaMemcpy(&c, d_c, sz, cudaMemcpyDeviceToHost));
    printf("Result is %d\n", c);

    CUDA_CHECK(cudaFree(d_a));
    CUDA_CHECK(cudaFree(d_b));
    CUDA_CHECK(cudaFree(d_c));
    return 0;
}

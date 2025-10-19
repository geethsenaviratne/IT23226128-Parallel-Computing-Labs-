#include <cstdio>
#include <cuda_runtime.h>
#include "cuda_check.hpp"

static void fill_random_ints(int* x, size_t n) {
    for (size_t i = 0; i < n; ++i) x[i] = rand() % 100;
}

__global__ void elemwiseMul2D(const int* __restrict__ A,
                              const int* __restrict__ B,
                              int* __restrict__ C,
                              int H, int W) {
    int c = blockIdx.x * blockDim.x + threadIdx.x; // column
    int r = blockIdx.y * blockDim.y + threadIdx.y; // row
    if (r < H && c < W) {
        size_t idx = (size_t)r * W + c;
        C[idx] = A[idx] * B[idx];
    }
}

int main() {
    const int H = 10'000;
    const int W = 10'000;
    const size_t N = (size_t)H * W;
    const size_t bytes = N * sizeof(int);

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

    dim3 block(32, 16); // 512 threads/block
    dim3 grid( (W + block.x - 1)/block.x,
               (H + block.y - 1)/block.y );

    elemwiseMul2D<<<grid, block>>>(dA, dB, dC, H, W);
    CUDA_CHECK(cudaDeviceSynchronize());

    CUDA_CHECK(cudaMemcpy(hC, dC, bytes, cudaMemcpyDeviceToHost));

    // Print last 1000 elements in last row
    int row = H - 1;         // 9999
    int from = W - 1000;     // 9000
    size_t base = (size_t)row * W;
    for (int c = from; c < W; ++c) {
        size_t idx = base + c;
        printf("C[%d][%d] = %d (A=%d, B=%d)\n", row, c, hC[idx], hA[idx], hB[idx]);
    }

    free(hA); free(hB); free(hC);
    CUDA_CHECK(cudaFree(dA));
    CUDA_CHECK(cudaFree(dB));
    CUDA_CHECK(cudaFree(dC));
    return 0;
}

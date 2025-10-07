// ex1_parallel_sum.c
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10000000

int main(int argc, char** argv) {
    int rank, size;
    long long local_sum = 0;
    long long total_sum = 0;
    int buffer_size;
    void* buffer;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Calculate range for this process
    long long chunk_size = N / size;
    long long start = rank * chunk_size + 1;
    long long end = (rank == size - 1) ? N : (rank + 1) * chunk_size;
    
    // Calculate local sum
    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }
    
    printf("Rank %d: Range [%lld-%lld], Local Sum = %lld\n", 
           rank, start, end, local_sum);
    
    if (rank != 0) {
        // Worker nodes: Send result to master using buffered send
        // Allocate buffer for MPI_Bsend
        buffer_size = MPI_BSEND_OVERHEAD + sizeof(long long);
        buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);
        
        MPI_Bsend(&local_sum, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
        
        // Detach buffer
        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
    } else {
        // Master node: Receive from all workers
        total_sum = local_sum;
        
        for (int i = 1; i < size; i++) {
            long long recv_sum;
            MPI_Status status;
            MPI_Recv(&recv_sum, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 
                     MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            total_sum += recv_sum;
            printf("Received from rank %d: %lld\n", status.MPI_SOURCE, recv_sum);
        }
        
        printf("\n=== FINAL RESULT ===\n");
        printf("Total Sum (1 to %d) = %lld\n", N, total_sum);
        printf("Expected: %lld\n", (long long)N * (N + 1) / 2);
    }
    
    MPI_Finalize();
    return 0;
}

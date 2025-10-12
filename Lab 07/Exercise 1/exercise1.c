#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    long long total = 0;
    long long n = 10000000;
    long long chunk_size = n / world_size;
    long long start = world_rank * chunk_size + 1;
    long long end = (world_rank == world_size - 1) ? n : start + chunk_size;
    
    long long local_sum = 0;
    for(long long i = start; i <= end; i++) {
        local_sum += i;
    }
    
    printf("Process %d: sum %lld to %lld = %lld\n", world_rank, start, end, local_sum);
    
    if(world_rank == 0) {
        total = local_sum;
        for(int i = 1; i < world_size; i++) {
            long long received;
            MPI_Status status;
            MPI_Recv(&received, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            total += received;
        }
        printf("Total sum 1 to %lld = %lld\n", n, total);
    } else {
        int buf_size = 1000;
        char* buffer = malloc(buf_size);
        MPI_Buffer_attach(buffer, buf_size);
        MPI_Bsend(&local_sum, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
        MPI_Buffer_detach(&buffer, &buf_size);
        free(buffer);
    }
    
    MPI_Finalize();
    return 0;
}

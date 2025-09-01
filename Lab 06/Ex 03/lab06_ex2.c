#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    long long n = 10000000;
    int rank, size;
    long long i, local_sum = 0, global_sum = 0;
    long long start, end;
    double t_start, t_end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Start timer only once at root
    if (rank == 0) {
        t_start = MPI_Wtime();
    }

    // Divide work among processes
    long long chunk = n / size;
    start = rank * chunk + 1;
    end = (rank == size - 1) ? n : start + chunk - 1;

    for (i = start; i <= end; i++) {
        local_sum += i;
    }

    // Reduce all partial sums into global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Stop timer and print result only at root
    if (rank == 0) {
        t_end = MPI_Wtime();
        printf("Sum from 1 to %lld = %lld\n", n, global_sum);
        printf("Time taken = %f seconds\n", t_end - t_start);
    }

    MPI_Finalize();
    return 0;
}

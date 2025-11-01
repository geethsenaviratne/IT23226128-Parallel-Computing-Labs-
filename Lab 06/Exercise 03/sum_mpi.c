#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    long long int N = 10000000;
    int rank, size;
    double start, end;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long int local_N = N / size;
    long long int start_num = rank * local_N + 1;
    long long int end_num = start_num + local_N - 1;

    long long int local_sum = 0;
    for (long long int i = start_num; i <= end_num; i++)
        local_sum += i;

    long long int total_sum = 0;
    start = MPI_Wtime();
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0) {
        printf("Total Sum = %lld\n", total_sum);
        printf("Time: %f seconds\n", end - start);
    }

    MPI_Finalize();
    return 0;
}

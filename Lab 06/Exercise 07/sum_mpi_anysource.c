/* sum_mpi_anysource.c
 * Sum numbers 1..N using point-to-point sends but root receives using MPI_ANY_SOURCE
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long long int N = 10000000;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc >= 2) N = atoll(argv[1]);

    long long int base = N / size;
    long long int rem = N % size;
    long long int local_n = base + (rank < rem ? 1 : 0);
    long long int start = rank < rem ? rank * (base+1) + 1 : rem*(base+1) + (rank-rem)*base + 1;
    long long int end = start + local_n - 1;

    long long int local_sum = 0;
    for (long long int i = start; i <= end; ++i) local_sum += i;

    if (rank == 0) {
        long long int total = local_sum;
        MPI_Status status;
        for (int i = 1; i < size; ++i) {
            long long int recvval = 0;
            /* receive from ANY source in any order */
            MPI_Recv(&recvval, 1, MPI_LONG_LONG_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Root: received %lld from rank %d\n", recvval, status.MPI_SOURCE);
            total += recvval;
        }
        printf("Total Sum (ANY_SOURCE) = %lld\n", total);
    } else {
        MPI_Send(&local_sum, 1, MPI_LONG_LONG_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

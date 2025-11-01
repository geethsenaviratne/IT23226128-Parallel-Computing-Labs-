/* message_mismatch.c
 * Demonstrates source/destination mismatch (sending to nonexistent rank)
 */

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int message = 12345;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        /* Trying to send to rank 2 even if size < 3 */
        printf("Rank 0: sending to rank 2 (may error or hang if rank 2 not present)\n");
        MPI_Send(&message, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        printf("Rank 0: send finished\n");
    } else if (rank == 1) {
        int recv;
        MPI_Recv(&recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 1: received %d\n", recv);
    }

    MPI_Finalize();
    return 0;
}

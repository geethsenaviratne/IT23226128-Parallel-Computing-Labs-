#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int message = 12345; /* do not rename this variable */
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) fprintf(stderr, "Run with at least 2 ranks\n");
        MPI_Finalize();
        return 1;
    }

    /* allocate Bsend buffer */
    int pack_size;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &pack_size);
    int bsize = pack_size + MPI_BSEND_OVERHEAD;
    void *buffer = malloc(bsize * 2); /* space for some messages */
    MPI_Buffer_attach(buffer, bsize * 2);

    if (rank == 0) {
        printf("Rank 0: calling MPI_Bsend(message=%d) to rank 1\n", message);
        MPI_Bsend(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Rank 0: MPI_Bsend returned\n");
    } else if (rank == 1) {
        int recv;
        MPI_Recv(&recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Rank 1: received %d\n", recv);
    }

    /* detach and free buffer */
    void *ptr; int bufsize;
    MPI_Buffer_detach(&ptr, &bufsize);
    free(buffer);

    MPI_Finalize();
    return 0;
}

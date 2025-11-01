#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    /* for sleep() */

int main(int argc, char *argv[]) {
    int rank, size;
    int message = 999;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) fprintf(stderr, "Run with at least 2 ranks\n");
        MPI_Finalize();
        return 1;
    }

    /* Prepare buffer for MPI_Bsend */
    int pack_size;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &pack_size);
    int bsize = pack_size + MPI_BSEND_OVERHEAD;
    void *buf = malloc(bsize * 2); /* allocate a bit more space */
    if (buf == NULL) {
        if (rank == 0) fprintf(stderr, "Failed to allocate Bsend buffer\n");
        MPI_Finalize();
        return 1;
    }
    MPI_Buffer_attach(buf, bsize * 2);

    if (rank == 0) {
        printf("Rank 0: MPI_Bsend -> rank 1 (message=%d)\n", message);
        MPI_Bsend(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        /* MPI_Bsend returns after copying into attached buffer */
        printf("Rank 0: returned from MPI_Bsend\n");
    } else if (rank == 1) {
        /* simulate delay so sender can return before receiver posts receive */
        sleep(1);
        int recv;
        MPI_Recv(&recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Rank 1: received %d\n", recv);
    }

    /* Detach and free buffer */
    void *ptr;
    int bufsize;
    MPI_Buffer_detach(&ptr, &bufsize);
    free(buf);

    MPI_Finalize();
    return 0;
}

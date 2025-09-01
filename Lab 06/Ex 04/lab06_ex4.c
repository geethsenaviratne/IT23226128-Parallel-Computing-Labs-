#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    const long long N = 10000000LL; // total samples
    int rank, size;
    long long i, local_in = 0, global_in = 0;
    long long start_idx, end_idx, chunk;
    double t0, t1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Divide work
    chunk = N / size;
    start_idx = rank * chunk;
    end_idx   = (rank == size - 1) ? N : start_idx + chunk;

    // Per-rank RNG (simple, deterministic seed)
    unsigned int seed = 12345u + (unsigned int)rank * 777u;

    if (rank == 0) t0 = MPI_Wtime();

    for (i = start_idx; i < end_idx; i++) {
        // Two uniform randoms in [0,1)
        double x = (double)rand_r(&seed) / (double)RAND_MAX;
        double y = (double)rand_r(&seed) / (double)RAND_MAX;
        double d2 = x*x + y*y;
        if (d2 <= 1.0) local_in++;
    }

    MPI_Reduce(&local_in, &global_in, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi_est = 4.0 * (double)global_in / (double)N;
        t1 = MPI_Wtime();
        printf("MPI Monte Carlo Pi\n");
        printf("Total samples: %lld\n", N);
        printf("Processes: %d\n", size);
        printf("Pi estimate: %.8f\n", pi_est);
        printf("Time (s): %.6f\n", t1 - t0);
        // one-line summary (easy for CSV scraping)
        fprintf(stderr, "PROCS=%d TIME=%.6f PI=%.8f\n", size, t1 - t0, pi_est);
    }

    MPI_Finalize();
    return 0;
}

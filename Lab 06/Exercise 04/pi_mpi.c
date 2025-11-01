#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char* argv[]) {
    long long int n = 10000000; /* total trials (can change here or extend to argv) */
    int rank, size;
    long long int local_count = 0;
    double x, y;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* Optional: allow passing N on command line */
    if (argc >= 2) {
        long long int tmp = atoll(argv[1]);
        if (tmp > 0) n = tmp;
    }

    /* divide n among ranks, distribute remainder to first 'rem' ranks */
    long long int base = n / size;
    long long int rem = n % size;
    long long int local_n = base + (rank < rem ? 1 : 0);

    /* seed RNG differently on each rank */
    unsigned int seed = (unsigned int) (time(NULL) ^ (rank * 7919));
    srand(seed);

    start = MPI_Wtime();
    for (long long int i = 0; i < local_n; i++) {
        x = (double)rand() / (double)RAND_MAX;
        y = (double)rand() / (double)RAND_MAX;
        if (x * x + y * y <= 1.0)
            local_count++;
    }
    end = MPI_Wtime();
    double local_elapsed = end - start;

    /* reduce counts and get max elapsed time across ranks */
    long long int total_count = 0;
    MPI_Reduce(&local_count, &total_count, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double max_elapsed = 0.0;
    MPI_Reduce(&local_elapsed, &max_elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi = 4.0 * (double)total_count / (double)n;
        /* single-line output containing N and ranks */
        printf("N=%lld ranks=%d pi=%.10f time=%f s\n", n, size, pi, max_elapsed);
    }

    MPI_Finalize();
    return 0;
}


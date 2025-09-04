#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <N> <threads>\n", argv[0]);
        return 1;
    }

    long long int N = atoll(argv[1]); // number of iterations
    int threads = atoi(argv[2]);     // number of threads
    double pi = 0.0;
    double tstart, tstop, tcalc;

    omp_set_num_threads(threads);

    tstart = omp_get_wtime();

    #pragma omp parallel for reduction(+:pi)
    for (long long int i = 0; i < N; i++) {
        pi += pow(-1, i) / (2.0 * i + 1.0);
    }
    pi *= 4.0;

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    printf("Threads: %d\n", threads);
    printf("Parallel Pi value: %.15f\n", pi);
    printf("Execution time (seconds): %f\n", tcalc);

    return 0;
}

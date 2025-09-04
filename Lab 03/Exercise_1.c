#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    long long int N = 1000000000; // large N for accuracy
    double pi = 0.0;
    double tstart, tstop, tcalc;

    tstart = omp_get_wtime();

    #pragma omp parallel for reduction(+:pi)
    for (long long int i = 0; i < N; i++) {
        double sign = (i % 2 == 0) ? 1.0 : -1.0;
        pi += sign / (2.0 * i + 1.0);
    }

    pi *= 4.0;

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    printf("Parallel Pi value: %.15f\n", pi);
    printf("Execution time (seconds): %f\n", tcalc);

    return 0;
}


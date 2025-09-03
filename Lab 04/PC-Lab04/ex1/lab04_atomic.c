// ----- lab04a_atomic.c -----
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    long long N = 100000000;
    double step = 1.0 / (double) N;
    double sum = 0.0;

    double start = omp_get_wtime();
    #pragma omp parallel for
    for (long long i = 1; i <= N; i++) {
        double x = (i - 0.5) * step;
        double temp = 1.0 / (1.0 + x * x);

        #pragma omp atomic
        sum += temp;
    }
    double pi = 4.0 * step * sum;
    double end = omp_get_wtime();

    printf("Parallel Pi (Atomic) = %.15f\n", pi);
    printf("Time (parallel - atomic): %f seconds\n", end - start);
    return 0;
}


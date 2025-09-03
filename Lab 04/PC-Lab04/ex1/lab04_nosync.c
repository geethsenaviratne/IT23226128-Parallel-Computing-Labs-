// ----- lab04a_nosync.c -----
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    long long N = 100000000;  // number of intervals
    double step = 1.0 / (double) N;
    double sum = 0.0;

    double start = omp_get_wtime();
    #pragma omp parallel for
    for (long long i = 1; i <= N; i++) {
        double x = (i - 0.5) * step;
        double temp = 1.0 / (1.0 + x * x);

        // ❌ No synchronization, all threads write to shared sum
        sum += temp;
    }
    double pi = 4.0 * step * sum;
    double end = omp_get_wtime();

    printf("Parallel Pi (No Sync) = %.15f\n", pi);
    printf("Time (parallel - nosync): %f seconds\n", end - start);
    return 0;
}

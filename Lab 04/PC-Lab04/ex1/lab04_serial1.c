// ----- lab04a_serial.c -----
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    long long N = 100000000;  // number of intervals
    double step = 1.0 / (double) N;
    double sum = 0.0;

    double start = omp_get_wtime();
    for (long long i = 1; i <= N; i++) {
        double x = (i - 0.5) * step;
        sum += 1.0 / (1.0 + x * x);
    }
    double pi = 4.0 * step * sum;
    double end = omp_get_wtime();

    printf("Serial Pi = %.15f\n", pi);
    printf("Time (serial): %f seconds\n", end - start);
    return 0;
}

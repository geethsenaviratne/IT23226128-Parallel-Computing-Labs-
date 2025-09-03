// ----- lab04a_critical.c -----
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    long long N = 100000000;  
    double step = 1.0 / (double) N;
    double sum = 0.0;

    double start = omp_get_wtime();
    #pragma omp parallel
    {
        double local_sum = 0.0;
        #pragma omp for
        for (long long i = 1; i <= N; i++) {
            double x = (i - 0.5) * step;
            local_sum += 1.0 / (1.0 + x * x);
        }
        #pragma omp critical
        sum += local_sum;
    }
    double pi = 4.0 * step * sum;
    double end = omp_get_wtime();

    printf("Parallel Pi (Critical) = %.15f\n", pi);
    printf("Time (parallel - critical): %f seconds\n", end - start);
    return 0;
}


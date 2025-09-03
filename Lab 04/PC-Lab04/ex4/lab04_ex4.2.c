#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    long long N = 100000000; // number of intervals
    double step = 1.0 / (double)N;
    double sum = 0.0, pi = 0.0;

    double tstart = omp_get_wtime();

    #pragma omp parallel shared(N, step) firstprivate(sum)
    {
        #pragma omp for
        for (long long i = 1; i <= N; i++) {
            double x = (i - 0.5) * step;
            double temp = 1.0 / (1.0 + x * x);
            #pragma omp atomic
            sum += temp;
        }
    }

    pi = 4.0 * step * sum;

    double tstop = omp_get_wtime();
    double tcalc = (tstop - tstart) * 1000.0; // ms

    printf("Parallel Approximation of pi = %.12f\n", pi);
    printf("Time taken = %.3f ms\n", tcalc);

    return 0;
}

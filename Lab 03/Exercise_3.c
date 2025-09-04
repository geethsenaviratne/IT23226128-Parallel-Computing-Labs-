// sum_omp.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }
    long long N = atoll(argv[1]);
    double sum = 0.0;

    double t0 = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (long long i = 1; i <= N; ++i) {
        // term = i - i^2 + sqrt(2*(i+1))
        double di = (double)i;
        double term = di - di*di + sqrt(2.0 * (di + 1.0));
        sum += term;
    }

    double t1 = omp_get_wtime();
    printf("N=%lld  sum=%g  time=%f sec  threads=%d\n",
           N, sum, t1 - t0, omp_get_max_threads());
    return 0;
}

#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 10000000   // 10 million terms

int main() {
    long long i;
    double sum = 0.0;
    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 1; i <= N; i++) {
        double temp = (i - i * i + sqrt(2.0 * (i + 1)));

        // Prevent race condition using atomic
        #pragma omp atomic
        sum += temp;
    }

    end = omp_get_wtime();

    printf("Summation (Atomic) = %.5f\n", sum);
    printf("Time taken: %f seconds\n", end - start);

    return 0;
}

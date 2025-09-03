#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define N 10000000  // 10 million

int main() {
    long inside = 0;

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        long local_count = 0;

        #pragma omp for
        for (long i = 0; i < N; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                local_count++;
            }
        }

        // Mutex/critical update
        #pragma omp critical
        {
            inside += local_count;
        }
    }

    double pi = 4.0 * (double)inside / N;
    double end = omp_get_wtime();

    printf("Parallel Pi = %.6f\n", pi);
    printf("Time (Parallel) = %.3f seconds\n", end - start);

    return 0;
}


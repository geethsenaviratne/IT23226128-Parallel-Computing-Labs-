#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    long long int num_points = 10000000; // 10 million points
    long long int inside_circle = 0;

    omp_lock_t lock;
    omp_init_lock(&lock);

    double tstart, tstop, tcalc;
    tstart = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num(); // thread-specific seed
        long long int local_count = 0;

        #pragma omp for
        for (long long int i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if (x*x + y*y <= 1.0) {
                local_count++;
            }
        }

        // Add to global count with mutex lock
        omp_set_lock(&lock);
        inside_circle += local_count;
        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock);

    double pi = 4.0 * inside_circle / num_points;

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    printf("Pi approximation: %.10f\n", pi);
    printf("Total points: %lld\n", num_points);
    printf("Points inside circle: %lld\n", inside

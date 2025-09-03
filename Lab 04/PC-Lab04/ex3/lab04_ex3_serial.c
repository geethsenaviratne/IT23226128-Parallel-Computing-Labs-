#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 10000000  // 10 million

int main() {
    long inside = 0;
    double x, y;

    double start = (double)clock() / CLOCKS_PER_SEC;

    srand(time(NULL));
    for (long i = 0; i < N; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            inside++;
        }
    }

    double pi = 4.0 * (double)inside / N;

    double end = (double)clock() / CLOCKS_PER_SEC;
    printf("Serial Pi = %.6f\n", pi);
    printf("Time (Serial) = %.3f seconds\n", end - start);

    return 0;
}



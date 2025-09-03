#include <stdio.h>
#include <math.h>

int main() {
    long long N = 100000000; // number of intervals
    double step = 1.0 / (double)N;
    double sum = 0.0;

    for (long long i = 1; i <= N; i++) {
        double x = (i - 0.5) * step;
        sum += 1.0 / (1.0 + x * x);
    }

    double pi = 4.0 * step * sum;
    printf("Sequential Approximation of pi = %.12f\n", pi);
    return 0;
}

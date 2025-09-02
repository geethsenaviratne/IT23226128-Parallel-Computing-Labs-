#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define MAX_ITER 2000     // maximum number of iterations
#define NPOINTS 1000      // resolution of the grid

int main() {
    int i, j, iter;
    int num_inside = 0;      // count how many points are inside the set
    double area, error;
    double ztemp, cr, ci, zr, zi;

    double start_time, end_time;

    // start timer
    start_time = omp_get_wtime();

    // parallelize the outer loop
    #pragma omp parallel for private(j, cr, ci, zr, zi, iter, ztemp) reduction(+:num_inside) schedule(static)
    for (i = 0; i < NPOINTS; i++) {
        for (j = 0; j < NPOINTS; j++) {
            // map grid (i,j) to complex plane: real [-2,1], imag [0,1.5]
            cr = -2.0 + 3.0 * (double) i / NPOINTS;
            ci = 1.5 * (double) j / NPOINTS;

            zr = cr;
            zi = ci;
            iter = 0;

            // Mandelbrot iteration
            do {
                ztemp = zr*zr - zi*zi + cr;
                zi = 2.0*zr*zi + ci;
                zr = ztemp;
                iter++;
            } while ((zr*zr + zi*zi < 4.0) && (iter < MAX_ITER));

            if (iter == MAX_ITER) {
                num_inside++;   // point is inside the set
            }
        }
    }

    // Estimate area (×2 for symmetry in lower half-plane)
    area = 2.0 * 3.0 * 1.5 * (double)num_inside / (NPOINTS * NPOINTS);
    error = area / sqrt((double)NPOINTS);

    // end timer
    end_time = omp_get_wtime();

    // output results
    printf("Threads used: %d\n", omp_get_max_threads());
    printf("Area of Mandelbrot set = %12.8f +/- %12.8f\n", area, error);
    printf("Time taken = %f seconds\n", end_time - start_time);

    return 0;
}


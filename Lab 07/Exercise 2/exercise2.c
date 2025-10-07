#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000  // 10,000 numbers

// Function to read numbers from the CSV file
void read_file(double *arr) {
    FILE *file = fopen("numbers.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        fscanf(file, "%lf,", &arr[i]);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    int rank, size;
    double numbers[N], local_sum = 0, total_sum = 0;
    double local_numbers[N / 4];  // Adjust this based on the number of nodes (for example, 4 nodes)
    clock_t start_time, end_time;
    double elapsed_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Reading CSV file...\n");
        read_file(numbers);  // Rank 0 reads the file
        printf("File read successfully!\n");
    }

    // Broadcast the numbers to all ranks
    MPI_Bcast(numbers, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Start the timer
    start_time = clock();

    // Each rank processes its chunk of the numbers
    int chunk_size = N / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? N : (rank + 1) * chunk_size;

    printf("Rank %d: Processing elements %d to %d, ", rank, start, end - 1);

    for (int i = start; i < end; i++) {
        local_sum += numbers[i];
    }

    printf("local sum = %.2f\n", local_sum);

    // Use MPI_Reduce to sum all the partial sums
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // End the timer
    end_time = clock();
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    if (rank == 0) {
        printf("Total Sum: %.2f\n", total_sum);
        printf("Time taken: %.4f seconds\n", elapsed_time);
    }

    MPI_Finalize();
    return 0;
}

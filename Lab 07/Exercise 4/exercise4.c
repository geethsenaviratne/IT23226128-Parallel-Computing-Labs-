#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_NUMBERS 10000

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int* all_numbers = NULL;
    int numbers_per_process = TOTAL_NUMBERS / world_size;
    int* local_numbers = (int*)malloc(numbers_per_process * sizeof(int));
    double total = 0;
    
    if(world_rank == 0) {
        all_numbers = (int*)malloc(TOTAL_NUMBERS * sizeof(int));
        FILE* file = fopen("numbers.csv", "r");
        for(int i = 0; i < TOTAL_NUMBERS; i++) {
            fscanf(file, "%d,", &all_numbers[i]);
        }
        fclose(file);
        printf("Root: Read %d numbers from file\n", TOTAL_NUMBERS);
    }
    
    // Scatter the data
    MPI_Scatter(all_numbers, numbers_per_process, MPI_INT, 
                local_numbers, numbers_per_process, MPI_INT, 
                0, MPI_COMM_WORLD);
    
    printf("Process %d: Received scattered data\n", world_rank);
    
    // Calculate partial sum
    double partial_sum = 0;
    for(int i = 0; i < numbers_per_process; i++) {
        partial_sum += local_numbers[i];
    }
    
    printf("Process %d: Partial sum = %.2f\n", world_rank, partial_sum);
    
    // Gather all partial sums at root
    double* partial_sums = NULL;
    if(world_rank == 0) {
        partial_sums = (double*)malloc(world_size * sizeof(double));
    }
    
    MPI_Gather(&partial_sum, 1, MPI_DOUBLE, 
               partial_sums, 1, MPI_DOUBLE, 
               0, MPI_COMM_WORLD);
    
    // Root calculates final total
    if(world_rank == 0) {
        for(int i = 0; i < world_size; i++) {
            total += partial_sums[i];
            printf("Partial sum from process %d: %.2f\n", i, partial_sums[i]);
        }
        printf("Final total sum: %.2f\n", total);
        free(all_numbers);
        free(partial_sums);
    }
    
    free(local_numbers);
    MPI_Finalize();
    return 0;
}

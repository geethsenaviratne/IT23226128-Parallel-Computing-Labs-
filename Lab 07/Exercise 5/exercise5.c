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
    double total = 0, partial_sum = 0;
    
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
    for(int i = 0; i < numbers_per_process; i++) {
        partial_sum += local_numbers[i];
    }
    
    printf("Process %d: Partial sum = %.2f\n", world_rank, partial_sum);
    
    // Use Reduce to sum all partial sums at root
    MPI_Reduce(&partial_sum, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(world_rank == 0) {
        printf("Final total sum: %.2f\n", total);
        free(all_numbers);
    }
    
    free(local_numbers);
    MPI_Finalize();
    return 0;
}

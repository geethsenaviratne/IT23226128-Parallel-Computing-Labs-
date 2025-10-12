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
    
    // Read file only in root process
    if(world_rank == 0) {
        all_numbers = (int*)malloc(TOTAL_NUMBERS * sizeof(int));
        FILE* file = fopen("numbers.csv", "r");
        if(file == NULL) {
            printf("Error opening file!\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        
        for(int i = 0; i < TOTAL_NUMBERS; i++) {
            fscanf(file, "%d,", &all_numbers[i]);
        }
        fclose(file);
        printf("Root: Read %d numbers from file\n", TOTAL_NUMBERS);
    }
    
    // Scatter the data to all processes
    MPI_Scatter(all_numbers, numbers_per_process, MPI_INT, 
                local_numbers, numbers_per_process, MPI_INT, 
                0, MPI_COMM_WORLD);
    
    printf("Process %d: Received scattered data\n", world_rank);
    
    // Each process calculates partial sum of its local data
    double partial_sum = 0;
    for(int i = 0; i < numbers_per_process; i++) {
        partial_sum += local_numbers[i];
    }
    
    printf("Process %d: Partial sum = %.2f\n", world_rank, partial_sum);
    
    // Send partial sums to root
    if(world_rank == 0) {
        total = partial_sum;
        for(int i = 1; i < world_size; i++) {
            double received_sum;
            MPI_Recv(&received_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total += received_sum;
        }
        printf("Final total sum: %.2f\n", total);
        free(all_numbers);
    } else {
        MPI_Send(&partial_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    
    free(local_numbers);
    MPI_Finalize();
    return 0;
}

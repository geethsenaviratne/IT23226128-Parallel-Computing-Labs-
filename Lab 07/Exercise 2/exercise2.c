#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_NUMBERS 10000

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int* numbers = NULL;
    double total = 0;
    
    // Read file only in root process
    if(world_rank == 0) {
        numbers = (int*)malloc(TOTAL_NUMBERS * sizeof(int));
        FILE* file = fopen("numbers.csv", "r");
        if(file == NULL) {
            printf("Error opening file! Make sure numbers.csv exists.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        
        for(int i = 0; i < TOTAL_NUMBERS; i++) {
            if(fscanf(file, "%d,", &numbers[i]) != 1) {
                printf("Error reading number at position %d\n", i);
                break;
            }
        }
        fclose(file);
        printf("Root: Read %d numbers from file\n", TOTAL_NUMBERS);
    }
    
    // Broadcast the array to all processes
    if(world_rank == 0) {
        MPI_Bcast(numbers, TOTAL_NUMBERS, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        numbers = (int*)malloc(TOTAL_NUMBERS * sizeof(int));
        MPI_Bcast(numbers, TOTAL_NUMBERS, MPI_INT, 0, MPI_COMM_WORLD);
    }
    
    printf("Process %d: Received broadcast data\n", world_rank);
    
    // Each process calculates partial sum
    int numbers_per_process = TOTAL_NUMBERS / world_size;
    int start = world_rank * numbers_per_process;
    int end = (world_rank == world_size - 1) ? TOTAL_NUMBERS : start + numbers_per_process;
    
    double partial_sum = 0;
    for(int i = start; i < end; i++) {
        partial_sum += numbers[i];
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
    } else {
        MPI_Send(&partial_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    
    free(numbers);
    MPI_Finalize();
    return 0;
}

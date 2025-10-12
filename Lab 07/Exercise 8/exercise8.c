#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 1000
#define NUM_CYCLES 2

int main(int argc, char** argv) {
    int rank, size;
    int array[MAX_ARRAY_SIZE];
    int array_length = 0;
    int next_rank, prev_rank;
    int total_passes;
    int current_pass = 0;
    MPI_Status status;
    double start_time, end_time;
    int i;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (size < 2) {
        if (rank == 0) {
            fprintf(stderr, "Error: This program requires at least 2 processes.\n");
            fprintf(stderr, "Usage: mpirun -np <num_processes> %s\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    // Calculate ring topology neighbors
    next_rank = (rank + 1) % size;
    prev_rank = (rank - 1 + size) % size;
    
    // Total passes = number of nodes × number of cycles
    total_passes = size * NUM_CYCLES;
    
    if (rank == 0) {
        printf("=== MPI Ring Topology Array Passing ===\n");
        printf("Number of processes: %d\n", size);
        printf("Number of cycles: %d\n", NUM_CYCLES);
        printf("Total passes through nodes: %d\n\n", total_passes);
        
        start_time = MPI_Wtime();
        
        // Node 0 processes all cycles
        for (current_pass = 0; current_pass < NUM_CYCLES; current_pass++) {
            if (current_pass == 0) {
                // First cycle: initialize and add rank
                array[array_length++] = rank;
                printf("[Rank %d] Pass %d: Added rank %d to array (length: %d)\n", 
                       rank, array_length, rank, array_length);
                
                // Send to next node
                MPI_Send(&array_length, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
                MPI_Send(array, array_length, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
                
                // Wait for array to complete first cycle
                MPI_Recv(&array_length, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(array, array_length, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, &status);
            } else {
                // Subsequent cycles: add rank and pass
                array[array_length++] = rank;
                printf("[Rank %d] Pass %d: Added rank %d to array (length: %d)\n", 
                       rank, array_length, rank, array_length);
                
                if (current_pass < NUM_CYCLES - 1) {
                    // Not the last cycle, continue
                    MPI_Send(&array_length, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
                    MPI_Send(array, array_length, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
                    
                    MPI_Recv(&array_length, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, &status);
                    MPI_Recv(array, array_length, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, &status);
                } else {
                    // Last cycle, just send
                    MPI_Send(&array_length, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
                    MPI_Send(array, array_length, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
                    
                    // Receive final result
                    MPI_Recv(&array_length, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, &status);
                    MPI_Recv(array, array_length, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, &status);
                }
            }
        }
        
        end_time = MPI_Wtime();
        
        printf("\n=== Ring Passing Complete ===\n");
        printf("Total time: %.6f seconds\n", end_time - start_time);
        printf("Final array length: %d\n", array_length);
        printf("\n=== Final Array Contents ===\n");
        
        for (i = 0; i < array_length; i++) {
            printf("%d ", array[i]);
            if ((i + 1) % 20 == 0) {
                printf("\n");
            }
        }
        printf("\n\n=== Verification ===\n");
        printf("Expected pattern: Each rank appears %d times\n", NUM_CYCLES);
        
        // Count occurrences of each rank
        int *rank_counts = (int*)calloc(size, sizeof(int));
        for (i = 0; i < array_length; i++) {
            rank_counts[array[i]]++;
        }
        
        printf("Rank occurrences:\n");
        for (i = 0; i < size; i++) {
            printf("  Rank %d: %d times\n", i, rank_counts[i]);
        }
        
        free(rank_counts);
        
    } else {
        // Non-root nodes process all cycles
        for (current_pass = 0; current_pass < NUM_CYCLES; current_pass++) {
            // Receive from previous node
            MPI_Recv(&array_length, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(array, array_length, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, &status);
            
            // Add own rank to array
            array[array_length++] = rank;
            
            int pass_num = current_pass * size + rank + 1;
            printf("[Rank %d] Pass %d: Added rank %d to array (length: %d)\n", 
                   rank, pass_num, rank, array_length);
            
            // Send to next node
            MPI_Send(&array_length, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
            MPI_Send(array, array_length, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
        }
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    if (rank == 0) {
        printf("\nAll processes completed successfully.\n");
    }
    
    MPI_Finalize();
    return 0;
}

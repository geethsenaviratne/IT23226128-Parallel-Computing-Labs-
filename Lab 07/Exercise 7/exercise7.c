#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_EXCHANGES 100
#define MAX_ARRAY_SIZE 200
#define MASTER 0
#define WORKER 1

int main(int argc, char** argv) {
    int rank, size;
    int array[MAX_ARRAY_SIZE];
    int array_length = 0;
    int i, exchange_count;
    MPI_Status status;
    double start_time, end_time;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (size != 2) {
        if (rank == 0) {
            fprintf(stderr, "Error: This program requires exactly 2 processes.\n");
            fprintf(stderr, "Usage: mpirun -np 2 %s\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    // Seed random number generator differently for each process
    srand(time(NULL) + rank);
    
    start_time = MPI_Wtime();
    
    if (rank == MASTER) {
        printf("=== MPI Ping-Pong Array Growth Program ===\n");
        printf("Starting ping-pong with %d message exchanges\n\n", MAX_EXCHANGES);
        
        // Master starts the ping-pong
        for (exchange_count = 0; exchange_count < MAX_EXCHANGES; exchange_count++) {
            // Generate and append random number
            int random_num = rand() % 1000;
            array[array_length++] = random_num;
            
            if (exchange_count < 5 || exchange_count >= MAX_EXCHANGES - 5) {
                printf("[Master] Exchange %d: Sending array of length %d (added %d)\n", 
                       exchange_count + 1, array_length, random_num);
            } else if (exchange_count == 5) {
                printf("[Master] ... (continuing) ...\n");
            }
            
            // Send array length first, then the array
            MPI_Send(&array_length, 1, MPI_INT, WORKER, 0, MPI_COMM_WORLD);
            MPI_Send(array, array_length, MPI_INT, WORKER, 0, MPI_COMM_WORLD);
            
            // Wait for response from worker (unless it's the last exchange)
            if (exchange_count < MAX_EXCHANGES - 1) {
                MPI_Recv(&array_length, 1, MPI_INT, WORKER, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(array, array_length, MPI_INT, WORKER, 0, MPI_COMM_WORLD, &status);
                
                if (exchange_count < 4 || exchange_count >= MAX_EXCHANGES - 6) {
                    printf("[Master] Exchange %d: Received array of length %d\n", 
                           exchange_count + 1, array_length);
                }
            }
        }
        
        end_time = MPI_Wtime();
        
        printf("\n=== Summary ===\n");
        printf("Total exchanges: %d\n", MAX_EXCHANGES);
        printf("Final array length: %d\n", array_length);
        printf("Total time: %.6f seconds\n", end_time - start_time);
        printf("Average time per exchange: %.6f seconds\n", 
               (end_time - start_time) / MAX_EXCHANGES);
        
        printf("\nFirst 10 elements: ");
        for (i = 0; i < 10 && i < array_length; i++) {
            printf("%d ", array[i]);
        }
        printf("\nLast 10 elements: ");
        for (i = (array_length > 10 ? array_length - 10 : 0); i < array_length; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
        
    } else if (rank == WORKER) {
        // Worker receives and responds
        for (exchange_count = 0; exchange_count < MAX_EXCHANGES; exchange_count++) {
            // Receive from master
            MPI_Recv(&array_length, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(array, array_length, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &status);
            
            if (exchange_count < 5 || exchange_count >= MAX_EXCHANGES - 5) {
                printf("[Worker] Exchange %d: Received array of length %d\n", 
                       exchange_count + 1, array_length);
            } else if (exchange_count == 5) {
                printf("[Worker] ... (continuing) ...\n");
            }
            
            // Add random number and send back (unless it's the last exchange)
            if (exchange_count < MAX_EXCHANGES - 1) {
                int random_num = rand() % 1000;
                array[array_length++] = random_num;
                
                if (exchange_count < 4 || exchange_count >= MAX_EXCHANGES - 6) {
                    printf("[Worker] Exchange %d: Sending back array of length %d (added %d)\n", 
                           exchange_count + 1, array_length, random_num);
                }
                
                MPI_Send(&array_length, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
                MPI_Send(array, array_length, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
            }
        }
    }
    
    MPI_Finalize();
    return 0;
}

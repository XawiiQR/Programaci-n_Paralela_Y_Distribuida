#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, comm_sz;
    int local_sum, global_sum = 0;

    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

        local_sum = rank + 1; 
        printf("Proceso %d: Valor inicial local = %d\n", rank, local_sum);

    
    int step = 1;
    int nivel = 1; 
    while (step < comm_sz) {
        if (rank % (2 * step) == 0) {
            
            if (rank + step < comm_sz) {
                int temp;
                printf("Nivel %d: Proceso %d esperando recibir de proceso %d\n", nivel, rank, rank + step);
                MPI_Recv(&temp, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Nivel %d: Proceso %d recibió %d de proceso %d -> Nueva suma local = %d\n", nivel, rank, temp, rank + step, local_sum + temp);
                local_sum += temp;
            }
        } else {
            
            int dest = rank - step;
            printf("Nivel %d: Proceso %d enviando su suma local %d a proceso %d\n", nivel, rank, local_sum, dest);
            MPI_Send(&local_sum, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            printf("Nivel %d: Proceso %d terminó su participación\n", nivel, rank);
            break; 
        }
        nivel++;
        step *= 2; 
    }

    
    if (rank == 0) {
        global_sum = local_sum;
        printf("\nResultado final:\n");
        printf("Proceso 0: La suma global es: %d\n", global_sum);
    }

    
    MPI_Finalize();
    return 0;
}

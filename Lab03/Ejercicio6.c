#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_value, received_value, global_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_value = rank + 1;

    printf("Proceso %d: Valor inicial local = %d\n", rank, local_value);

    int step = 1;
    while (step < size) {
        if (rank % (2 * step) == 0) {
            if (rank + step < size) {
                MPI_Recv(&received_value, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                local_value += received_value;
                printf("Proceso %d: Recibió %d de proceso %d -> Nueva suma local = %d\n", rank, received_value, rank + step, local_value);
            }
        } else {
            MPI_Send(&local_value, 1, MPI_INT, rank - step, 0, MPI_COMM_WORLD);
            printf("Proceso %d: Enviando su suma local %d a proceso %d\n", rank, local_value, rank - step);
            break;
        }
        step *= 2;
    }

    if (rank == 0) {
        global_sum = local_value;
        printf("Resultado final: Proceso 0: La suma global es %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}

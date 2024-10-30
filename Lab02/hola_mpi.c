#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa el entorno MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtiene el rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtiene el número total de procesos

    printf("Hola desde el proceso %d de %d\n", rank, size);

    MPI_Finalize(); // Finaliza el entorno MPI
    return 0;
}

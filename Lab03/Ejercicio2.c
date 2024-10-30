#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int total_darts = 1000000000; // Total de lanzamientos de dardos

double random_double() {
    return (double)rand() / RAND_MAX * 2.0 - 1.0;
}

int main(int argc, char *argv[]) {
    int rank, size;
    long long int local_count = 0;  
    long long int global_count = 0; 
    long long int local_darts; 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Proceso 0: Número total de procesos = %d\n", size);
        printf("Proceso 0: Número total de lanzamientos de dardos asignados inicialmente = %lld\n", total_darts);
    }

    MPI_Bcast(&total_darts, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);

    local_darts = total_darts / size;
    if (rank == 0) {
        local_darts += total_darts % size;  
    }

    printf("Proceso %d: lanzamientos asignados después de repartir = %lld\n", rank, local_darts);

    srand(rank + 1);

    for (long long int i = 0; i < local_darts; i++) {
        double x = random_double();
        double y = random_double();
        if ((x * x + y * y) <= 1.0) {
            local_count++;
        }
    }

    printf("Proceso %d: Lanzamientos dentro del círculo = %lld de %lld\n", rank, local_count, local_darts);

    MPI_Reduce(&local_count, &global_count, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi_estimate = 4.0 * (double)global_count / (double)total_darts;
        printf("Proceso 0: Conteo global de lanzamientos dentro del círculo = %lld\n", global_count);
        printf("Proceso 0: Estimación de π = %.10f\n", pi_estimate);
    } else {        printf("Proceso %d: No tiene más tareas.\n", rank);
    }

    MPI_Finalize();
    return 0;
}

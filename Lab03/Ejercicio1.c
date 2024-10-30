#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 20
#define BINS 5

int main(int argc, char *argv[]) {
    int rank, size;
    float data[DATA_SIZE] = {1.3, 2.9, 0.4, 0.3, 1.3, 4.4, 1.7, 0.4, 3.2, 0.3,
                             4.9, 2.4, 3.1, 4.4, 3.9, 0.4, 4.2, 4.5, 4.9, 0.9};
    int bin_counts[BINS] = {0};
    int local_bin_counts[BINS] = {0};
    float bin_maxes[BINS];
    float min_meas = 0.0, max_meas = 5.0;
    float bin_width = (max_meas - min_meas) / BINS;

    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
    printf("Proceso %d iniciado de un total de %d procesos\n", rank, size);

    
    int chunk_size = DATA_SIZE / size;
    float *local_data = (float *)malloc(chunk_size * sizeof(float));

    
    if (rank == 0) {
        printf("Proceso 0: Inicializando límites de bins...\n");
        for (int i = 0; i < BINS; i++) {
            bin_maxes[i] = min_meas + bin_width * (i + 1);
            printf("Bin %d: %.1f - %.1f\n", i, (i == 0 ? min_meas : bin_maxes[i-1]), bin_maxes[i]);
        }
        printf("Proceso 0: Distribuyendo datos a otros procesos...\n");
    }

    
    MPI_Bcast(bin_maxes, BINS, MPI_FLOAT, 0, MPI_COMM_WORLD);

    
    MPI_Scatter(data, chunk_size, MPI_FLOAT, local_data, chunk_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
    printf("Proceso %d: Recibí mis datos y empezaré a contar en bins\n", rank);

    
    for (int i = 0; i < chunk_size; i++) {
        int bin = (int)((local_data[i] - min_meas) / bin_width);
        if (bin >= BINS) bin = BINS - 1; 
        local_bin_counts[bin]++;
    }

    
    printf("Proceso %d: Conteo local de bins:\n", rank);
    for (int i = 0; i < BINS; i++) {
        printf("  Bin %d: %d\n", i, local_bin_counts[i]);
    }

        MPI_Reduce(local_bin_counts, bin_counts, BINS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    
    if (rank == 0) {
        printf("Proceso 0: Histograma final:\n");
        for (int i = 0; i < BINS; i++) {
            printf("  Bin %d (%.1f - %.1f): %d\n", i, (i == 0 ? min_meas : bin_maxes[i-1]), bin_maxes[i], bin_counts[i]);
        }
    }

    
    free(local_data);
    MPI_Finalize();
    return 0;
}

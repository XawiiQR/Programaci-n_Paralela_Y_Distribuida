#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;

const int num = 100; // Define el tamaño base de la matriz

// Multiplicación de matrices clásica
void MultiplicarMatricesClasica(const vector<vector<double>>& A, const vector<vector<double>>& B, vector<vector<double>>& C, int MAX) {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < MAX; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Multiplicación de matrices por bloques
void MultiplicarMatricesPorBloques(const vector<vector<double>>& A, const vector<vector<double>>& B, vector<vector<double>>& C, int MAX, int tamBloque) {
    for (int ii = 0; ii < MAX; ii += tamBloque) {
        for (int jj = 0; jj < MAX; jj += tamBloque) {
            for (int kk = 0; kk < MAX; kk += tamBloque) {
                // Multiplicación de los bloques
                for (int i = ii; i < min(ii + tamBloque, MAX); ++i) {
                    for (int j = jj; j < min(jj + tamBloque, MAX); ++j) {
                        for (int k = kk; k < min(kk + tamBloque, MAX); ++k) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

void CrearMatriz(vector<vector<double>>& A, vector<vector<double>>& B, int MAX) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = rand() % 1000;
            B[i][j] = rand() % 1000;
        }
    }
}

int main() {
    int MAX = 0; // Tamaño de la matriz
    int tamBloque = 100; // Tamaño del bloque
    for(int i=1; i<20; i++)
        {
        MAX= i*num;
    // Definir matrices A, B y C de tamaño MAX
        vector<vector<double>> A(MAX, vector<double>(MAX));
        vector<vector<double>> B(MAX, vector<double>(MAX));
        vector<vector<double>> C(MAX, vector<double>(MAX, 0.0)); // Inicializar C con ceros
    
        // Crear matrices aleatorias
        CrearMatriz(A, B, MAX);
    
        // Multiplicación clásica
        auto start_clasica = chrono::high_resolution_clock::now();
        MultiplicarMatricesClasica(A, B, C, MAX);
        auto end_clasica = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion_clasica = end_clasica - start_clasica;
        cout << "Tiempo de multiplicación clásica: " << fixed << setprecision(9) << duracion_clasica.count() << " segundos." << endl;
    
        // Reiniciar matriz C para multiplicación por bloques
        C.assign(MAX, vector<double>(MAX, 0.0));
    
        // Multiplicación por bloques
        auto start_bloques = chrono::high_resolution_clock::now();
        MultiplicarMatricesPorBloques(A, B, C, MAX, tamBloque);
        auto end_bloques = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion_bloques = end_bloques - start_bloques;
        cout << "Tiempo de multiplicación por bloques: " << fixed << setprecision(9) << duracion_bloques.count() << " segundos." << endl;
    }
    return 0;
}

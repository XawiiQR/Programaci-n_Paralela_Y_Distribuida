#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>

const int MAX = 10000; // Define el tamaño de la matriz

int main() {
    
    
    //for (int k=0; k<5;k++){
        
        //int MAX = k*num;
        std::vector<std::vector<double>> A(MAX, std::vector<double>(MAX));
        std::vector<std::vector<double>> B(MAX, std::vector<double>(MAX));
        //std::vector<double> x(MAX), y(MAX, 0);
        // Inicializar la matriz A y el vector x
        
        
        for (int i = 0; i < MAX; i++) {
            //x[i] = rand() % 1000;
            for (int j = 0; j < MAX; j++) {
                A[i][j] = rand() % 1000;
                B[i][j] = rand() % 1000;
            }
        }
    
        // Primer par de bucles: Orden fila
        
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                y[i] += A[i][j] * x[j];
            
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time: " << std::fixed << std::setprecision(9)<<duration.count() << " segundos." << std::endl;
        
    
        // Reiniciar el vector y para el segundo bucle
        std::fill(y.begin(), y.end(), 0);
    
        
        auto start2 = std::chrono::high_resolution_clock::now();
        // Segundo par de bucles: Orden columna
        for (int j = 0; j < MAX; j++)
            for (int i = 0; i < MAX; i++)
                y[i] += A[i][j] * x[j];
    
    
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration2 = end2 - start2;
        std::cout << "Time: " << std::fixed << std::setprecision(9)<< duration2.count() << " segundos." << std::endl;
        
        std::cout << "Time Diference: " << std::fixed << std::setprecision(9)<< abs(duration.count()-duration2.count())<< " segundos." << std::endl;
    //}
    return 0;
}

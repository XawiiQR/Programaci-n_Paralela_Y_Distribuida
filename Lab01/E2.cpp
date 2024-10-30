#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

int main(){
    int num =100;
    int MAX =0;
    for(int i = 1; i <= 10; i++){
        MAX= i*num;
        vector<vector<double>> A(MAX, vector<double>(MAX));
        vector<vector<double>> B(MAX, vector<double>(MAX));
        vector<vector<double>> result(MAX, vector<double>(MAX,0.0));
        
        for(int i = 0; i < MAX; i++){
            for(int j = 0; j < MAX; j++){
                A[i][j] = rand() % 1000;
                B[i][j] = rand() % 1000;
            }
        }
        //multiplate vector A and B
        auto start = high_resolution_clock::now();
        for(int i = 0; i < MAX; i++){
            for(int j = 0; j < MAX; j++){
                for(int k = 0; k < MAX; k++){
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        auto end = high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Tiempo: " << duration.count() << " Segundos" << endl;
        //cout<< duration_cast<microseconds>(end - start).count() << endl;
    }
    //file.close();
    return 0;
}
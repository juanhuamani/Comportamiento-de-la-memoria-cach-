#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

const int BLOCK_SIZE = 32; 

void multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; i += BLOCK_SIZE) {
        for (int j = 0; j < n; j += BLOCK_SIZE) {
            for (int k = 0; k < n; k += BLOCK_SIZE) {
                for (int ii = i; ii < min(i + BLOCK_SIZE, n); ++ii) {
                    for (int jj = j; jj < min(j + BLOCK_SIZE, n); ++jj) {
                        for (int kk = k; kk < min(k + BLOCK_SIZE, n); ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    vector<int> tamaños = {100, 150 , 200, 250, 300, 350, 400, 450, 500, 550, 600}; 

    ofstream archivo("resultados_multiplicacion_bloques.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo!" << endl;
        return 1;
    }

    for (int n : tamaños) {
        vector<vector<int>> A(n, vector<int>(n, 1));  
        vector<vector<int>> B(n, vector<int>(n, 1)); 
        vector<vector<int>> C(n, vector<int>(n, 0)); 

        auto start = high_resolution_clock::now();
        multiplyMatrices(A, B, C);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();

        archivo << n << " " << duration << endl;
    }

    archivo.close();

    return 0;
}
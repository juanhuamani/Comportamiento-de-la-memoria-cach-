#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

const int BLOCK_SIZE = 16; 

void multiplyMatricesBlock(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
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

void multiplyMatricesClassic(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0; 
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

long long medirTiempoMultiplicacionBloques(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    auto start = high_resolution_clock::now();
    multiplyMatricesBlock(A, B, C);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    return duration;
}

long long medirTiempoMultiplicacionClasica(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    auto start = high_resolution_clock::now();
    multiplyMatricesClassic(A, B, C);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    return duration.count();
}

int main() {
    vector<int> tamaños = { 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000 };

    ofstream archivoBloques("resultados_multiplicacion_bloques.txt");
    ofstream archivoClasico("resultados_multiplicacion_clasica.txt");
    if (!archivoBloques.is_open() || !archivoClasico.is_open()) {
        cerr << "Error al abrir los archivos!" << endl;
        return 1;
    }

    for (int n : tamaños) {
        cout << "Probando con tamaño: " << n << endl;
        vector<vector<int>> A(n, vector<int>(n));
        vector<vector<int>> B(n, vector<int>(n));
        vector<vector<int>> C(n, vector<int>(n, 0));
        vector<vector<int>> D(n, vector<int>(n, 0)); 

        srand(time(0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }

        long long tiempoBloques = medirTiempoMultiplicacionBloques(A, B, C);
        archivoBloques << n << " " << tiempoBloques << endl;

        long long tiempoClasico = medirTiempoMultiplicacionClasica(A, B, D);
        archivoClasico << n << " " << tiempoClasico << endl;
    }

    archivoBloques.close();
    archivoClasico.close();

    return 0;
}
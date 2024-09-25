#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
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

long long medirTiempoMultiplicacion(int n) {
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));
    vector<vector<int>> C(n, vector<int>(n, 0));

    srand(time(0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
    auto start = high_resolution_clock::now();
    multiplyMatrices(A, B, C);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    return duration.count();
}

int main() {
    vector<int> tamaños = {200 , 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000};   

    ofstream archivo("resultados_multiplicacion_clasica.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo!" << endl;
        return 1;
    }
    for (int n : tamaños) {
        long long tiempo = medirTiempoMultiplicacion(n);
        archivo << n << " " << tiempo << endl;  
    }

    archivo.close();

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int main(){
    srand(time(0));
    ofstream filefirst("primerArchivo.txt");
    ofstream filesecond("segundoArchivo.txt");
    
    vector<int> MAX_ARRAY;
    
    for(int i = 1; i <= 100; i++){
        MAX_ARRAY.push_back(i*100);
    }
    
    for(int &MAX: MAX_ARRAY){
        vector<vector<double>> A(MAX, vector<double>(MAX));
        vector<double> x(MAX), y(MAX, 0.0);

        for (int i = 0; i < MAX; i++) {
            x[i] = rand() % 1000;
            for (int j = 0; j < MAX; j++) {
                A[i][j] = rand() % 1000;
            }
        }

        auto start = high_resolution_clock::now();
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                y[i] += A[i][j] * x[j];
            }
        }
        auto end = high_resolution_clock::now();
        filefirst << duration_cast<microseconds>(end - start).count() << endl;

        fill(y.begin(), y.end(), 0.0);

        start = high_resolution_clock::now();
        for (int j = 0; j < MAX; j++) {
            for (int i = 0; i < MAX; i++) {
                y[i] += A[i][j] * x[j];
            }
        }
        end = high_resolution_clock::now();
        filesecond << duration_cast<microseconds>(end - start).count() << endl;
    }

    filefirst.close();
    filesecond.close();

    return 0;
}
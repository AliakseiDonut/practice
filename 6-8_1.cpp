#include <iostream>
#include <cmath>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class Matrix {
private:
    int size;
    int** data;

public:
    Matrix(int n) {
        size = n;
        data = new int* [size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size];
        }
    }

    void fillMatrix() {
        srand(time(0));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                data[i][j] = rand() % 10;
            }
        }
    }

    void printMatrix() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    double calculateFirstNorm() {
        double norm = 0;
        for (int i = 0; i < size; i++) {
            double sum = 0;
            for (int j = 0; j < size; j++) {
                sum += abs(data[j][i]);
            }
            if (sum > norm) {
                norm = sum;
            }
        }
        return norm;
    }

    double calculateSecondNorm() {
        double norm = 0;
        for (int i = 0; i < size; i++) {
            double sum = 0;
            for (int j = 0; j < size; j++) {
                sum += abs(data[i][j]);
            }
            if (sum > norm) {
                norm = sum;
            }
        }
        return norm;
    }

    ~Matrix() {
        for (int i = 0; i < size; i++) {
            delete[] data[i];
        }
        delete[] data;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int m, n;
    cout << "Введите количество матриц: ";
    cin >> m;
    cout << "Введите размер матриц (n x n): ";
    cin >> n;



    Matrix** matrices = new Matrix * [m];
    for (int i = 0; i < m; i++) {
        matrices[i] = new Matrix(n);
        matrices[i]->fillMatrix();
        cout << "Матрица " << i + 1 << ":" << endl;
        matrices[i]->printMatrix();
    }

    int minFirstNormIndex = 0;
    int minSecondNormIndex = 0;
    double minFirstNorm = matrices[0]->calculateFirstNorm();
    double minSecondNorm = matrices[0]->calculateSecondNorm();

    for (int i = 1; i < m; i++) {
        double firstNorm = matrices[i]->calculateFirstNorm();
        if (firstNorm < minFirstNorm) {
            minFirstNorm = firstNorm;
            minFirstNormIndex = i;
        }

        double secondNorm = matrices[i]->calculateSecondNorm();
        if (secondNorm < minSecondNorm) {
            minSecondNorm = secondNorm;
            minSecondNormIndex = i;
        }
    }

    cout << "Матрица с наименьшей первой нормой находится под индексом " << ++minFirstNormIndex << " с нормой " << minFirstNorm << endl;
    cout << "Матрица с наименьшей второй нормой находится под индексом " << ++minSecondNormIndex << " с нормой " << minSecondNorm << endl;

    for (int i = 0; i < m; i++) {
        delete matrices[i];
    }
    delete[] matrices;

    return 0;
}

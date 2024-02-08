#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

class Vector {
private:
    vector<double> elements;
public:
    Vector(int size) {
        elements.resize(size);
    }

    int getSize() const {
        return elements.size();
    }

    double& operator[](int index) {
        return elements[index];
    }

    const double& operator[](int index) const {
        return elements[index];
    }

    friend istream& operator>>(istream& in, Vector& vector) {
        for (int i = 0; i < vector.getSize(); ++i) {
            in >> vector[i];
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Vector& vector) {
        for (int i = 0; i < vector.getSize(); ++i) {
            out << vector[i] << " ";
        }
        return out;
    }

    friend bool isCollinear(const Vector& v1, const Vector& v2) {
        if (v1.getSize() != v2.getSize()) {
            return false;
        }

        double factor = v2[0] / v1[0];
        for (int i = 1; i < v1.getSize(); ++i) {
            if (v2[i] / v1[i] != factor) {
                return false;
            }
        }

        return true;
    }

    friend bool isOrthogonal(const Vector& v1, const Vector& v2) {
        if (v1.getSize() != v2.getSize()) {
            return false;
        }

        double dotProduct = 0.0;
        for (int i = 0; i < v1.getSize(); ++i) {
            dotProduct += v1[i] * v2[i];
        }

        return dotProduct == 0.0;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int m, n;
    cout << "Введите количество векторов (m): ";
    cin >> m;
    cout << "Введите размерность векторов (n): ";
    cin >> n;

    vector<Vector> vectors(m, Vector(n));

    cout << "Введите " << m << " векторов размерности " << n << ":\n";
    for (int i = 0; i < m; ++i) {
        cout << "Вектор " << i + 1 << ": ";
        cin >> vectors[i];
    }

    cout << "Коллинерные векторы:\n";
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (isCollinear(vectors[i], vectors[j])) {
                cout << "Вектор " << i + 1 << " и Вектор " << j + 1 << ": "
                    << vectors[i] << ", " << vectors[j] << endl;
            }
        }
    }

    cout << "Ортогональные векторы:\n";
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (isOrthogonal(vectors[i], vectors[j])) {
                cout << "Вектор " << i + 1 << " и Вектор " << j + 1 << ": "
                    << vectors[i] << ", " << vectors[j] << endl;
            }
        }
    }

    return 0;
}
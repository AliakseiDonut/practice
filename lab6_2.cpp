#include <iostream> 
#include <cmath> 
#include <Windows.h> 
#include <cstdlib>
#include <fstream> 
#include <string>
#include <sstream>
using namespace std;

class Polynom {
public:
    int n;
    double* koef;
    Polynom();
    Polynom(int k);
    Polynom(int k, double* mas);
    Polynom(const Polynom& ob);
    ~Polynom() { delete[] koef; }
    void GiveMemory(int k);
    void SetPolynom(int k, double* mas);
    void SetDegree(int k) { n = k; }
    void CalculateValue(double x);
    int GetDegree() const { return n; }
    double GetOneCoefficient(int i) const { return (koef[i]); }
    Polynom sum(Polynom pol);
    Polynom dif(Polynom pol);
    Polynom prod(Polynom pol);
    Polynom operator+(const Polynom& ob) const;
    Polynom operator*(const Polynom& ob);
    Polynom operator-(const Polynom& ob) const;
    Polynom& operator--();
    Polynom& operator++();
    double& operator[](int i) { return (koef[i]); }
    Polynom& operator=(const Polynom& p) {
        if (&p == this) return *this;
        if (koef) delete[] koef;
        n = p.n;
        koef = new double[p.n + 1];
        for (int i = 0; i <= p.n; i++)
            koef[i] = p.koef[i];
        return *this;
    }
};

Polynom Polynom::sum(Polynom pol) {
    return *this + pol;
}

Polynom Polynom::dif(Polynom pol) {
    return *this - pol;
}

Polynom Polynom::prod(Polynom pol) {
    return *this * pol;
}

ostream& operator<<(std::ostream& os, const Polynom& p) {
    for (int i = p.GetDegree(); i >= 0; i--) {
        os << p.GetOneCoefficient(i) << "x^" << i;
        if (i > 0) {
            os << " + ";
        }
    }
    return os;
}

istream& operator>>(istream& is, Polynom& polynom) {
    cout << "Введите степень полинома: ";
    is >> polynom.n;

    polynom.koef = new double[polynom.n + 1];

    cout << "Введите коэффициенты: ";
    for (int i = polynom.n; i >= 0; i--)
        is >> polynom.koef[i];

    return is;
}

Polynom::Polynom() {
    cout << "Введите степень полинома: ";
    cin >> n;
    koef = new double[n + 1];
    cout << "Введите коэффиценты: ";
    for (int i = n; i >= 0; i--)
        cin >> koef[i];
}

Polynom::Polynom(int k) {
    n = k;
    koef = new double[n + 1];
    cout << "Введите коэффиценты: ";
    for (int i = n; i >= 0; i--)
        cin >> koef[i];
}

Polynom::Polynom(int k, double* mas) {
    n = k;
    koef = new double[n + 1];
    for (int i = n; i >= 0; i--)
        koef[i] = mas[i];
}

Polynom::Polynom(const Polynom& ob) {
    n = ob.n;
    koef = new double[n + 1];
    for (int i = 0; i <= n; i++)
        koef[i] = ob.koef[i];
}


void Polynom::GiveMemory(int k) {
    if (koef) delete[] koef;
    koef = new double[k + 1];
}

void Polynom::SetPolynom(int k, double* mas) {
    n = k;
    if (koef) delete[] koef;
    koef = new double[n + 1];
    for (int i = n; i >= 0; i--)
        koef[i] = mas[i];
}

void Polynom::CalculateValue(double x) {
    double s = 0.0;
    for (int i = 0; i <= n; i++)
        s += koef[i] * pow(x, i);
    cout << "f(" << x << ") = " << s << endl;
    std::ofstream outFile("result.txt");
    outFile << "f(" << x << ") = " << s << endl;
    outFile.close();
}

Polynom Polynom::operator+(const Polynom& ob) const {
    int degree = max(n, ob.n);
    Polynom result(*this);
    result.GiveMemory(degree);
    for (int i = 0; i <= min(n, ob.n); i++)
        result.koef[i] = koef[i] + ob.koef[i];
    if (n < ob.n) {
        for (int i = min(n, ob.n) + 1; i <= ob.n; i++)
            result.koef[i] = ob.koef[i];
        result.n = ob.n;
    }
    else {
        for (int i = min(n, ob.n) + 1; i <= n; i++)
            result.koef[i] = koef[i];
        result.n = n;
    }
    return result;
}

Polynom Polynom::operator-(const Polynom& ob) const {
    int degree = max(n, ob.n);
    Polynom result(*this);
    result.GiveMemory(degree);
    for (int i = 0; i <= min(n, ob.n); i++)
        result.koef[i] = koef[i] - ob.koef[i];
    if (n < ob.n) {
        for (int i = min(n, ob.n) + 1; i <= ob.n; i++)
            result.koef[i] = -ob.koef[i];
        result.n = ob.n;
    }
    else {
        for (int i = min(n, ob.n) + 1; i <= n; i++)
            result.koef[i] = koef[i];
        result.n = n;
    }
    return result;
}

Polynom Polynom::operator*(const Polynom& ob) {
    int degree = n + ob.n;
    Polynom result(*this);
    result.GiveMemory(degree);
    for (int i = 0; i <= degree; i++) {
        result.koef[i] = 0.0;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= ob.n; j++) {
            result.koef[i + j] += koef[i] * ob.koef[j];
        }
    }
    result.n = degree;
    return result;
}

Polynom& Polynom::operator--() {
    for (int i = 0; i <= n; i++) {
        koef[i]--;
    }
    return *this;
}

Polynom& Polynom::operator++() {
    for (int i = 0; i <= n; i++) {
        koef[i]++;
    }
    return *this;
}

void addPolynomsToFile() {
    int polynomsQuantity;
    cout << "Введите количество полиномов: ";
    cin >> polynomsQuantity;

    ofstream fout;
    fout.open("polynoms.txt", ofstream::app);

    try {
        if (!fout.is_open()) {
            throw runtime_error("Ошибка: не удалось открыть файл для записи.");
        }

        for (int i = 0; i < polynomsQuantity; i++) {
            int degree = rand() % 10 + 1;
            double* coefficients = new double[degree + 1];
            for (int j = 0; j <= degree; j++) {
                coefficients[j] = (rand() % 21) - 10;
            }
            Polynom polynom(degree, coefficients);
            fout << polynom << endl;
            delete[] coefficients;
        }

        fout.close();

        cout << "Полиномы успешно добавлены в файл." << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}
void reverseArray(double* coefficients, int numTerms) {
    int start = 0;
    int end = numTerms - 1;

    while (start < end) {
        double temp = coefficients[start];
        coefficients[start] = coefficients[end];
        coefficients[end] = temp;
        start++;
        end--;
    }
}
double* parseString(const string& equation, int& numTerms) {
    double* coefficients = new double[equation.length()];
    string term;
    int start = 0;
    int end = 0;
    while (end < equation.length()) {
        if (equation[end] == '+') {
            term = equation.substr(start, end - start);
            coefficients[numTerms++] = std::stod(term);
            start = end + 1;
        }
        end++;
    }

    term = equation.substr(start, end - start);
    coefficients[numTerms++] = std::stod(term);
    reverseArray(coefficients, numTerms);
    return coefficients;
}
Polynom sumArray(Polynom** array, int size) {
    Polynom sum = *array[0];
    for (int i = 1; i < size; i++) {
        sum = sum + *array[i];
    }
    return sum;
}
void readPolynomsFromFile() {
    ifstream fin;
    fin.open("polynoms.txt");
    string line;
    int numPolynoms = 0;
    Polynom** polynomsArray = nullptr;

    try {
        if (!fin.is_open()) {
            throw runtime_error("Ошибка: не удалось открыть файл для чтения.");
        }

        while (getline(fin, line)) {
            int numTerms = 0;
            double* koef = parseString(line, numTerms);
            Polynom* polynom = new (nothrow) Polynom(numTerms - 1, koef);

            if (polynom == nullptr) {
                throw bad_alloc();
            }

            Polynom** tempArray = new (nothrow) Polynom * [numPolynoms + 1];
            if (tempArray == nullptr) {
                delete polynom;
                throw bad_alloc();
            }

            for (int i = 0; i < numPolynoms; i++) {
                tempArray[i] = polynomsArray[i];
            }
            tempArray[numPolynoms] = polynom;

            delete[] polynomsArray;
            polynomsArray = tempArray;
            delete[] koef;
            numPolynoms++;
        }

        Polynom sum = sumArray(polynomsArray, numPolynoms);
        for (int i = 0; i < numPolynoms; i++) {
            cout << *(polynomsArray[i]) << endl;
        }
        cout << "Сумма полиномов: " << sum << endl;
        for (int i = 0; i < numPolynoms; i++) {
            delete polynomsArray[i];
        }
        delete[] polynomsArray;
        fin.close();
    }
    catch (const bad_alloc& e) {
        cout << "Ошибка: Недостаточно памяти." << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

int main() {

    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    int choice;

    Polynom initialSum;

    std::ofstream outFile("result.txt");

    while (true) {
        cout << "Menu:\n";
        cout << "1. Выполнить операцию с полиномами\n";
        cout << "2. Вычислить значение полинома\n";
        cout << "3. Добавить полиномы в файл\n";
        cout << "4. Посчитать сумму полиномов из файла\n";
        cout << "5. Инкремент\n";
        cout << "6. Декремент\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        if (choice == 1) {
            int operation;
            cout << "Выберите операцию:\n";
            cout << "1. Сложение\n";
            cout << "2. Вычитание\n";
            cout << "3. Умножение\n";
            cout << "Введите номер операции: ";
            cin >> operation;

            switch (operation) {
            case 1: {
                Polynom p1, p2;
                Polynom sum = p1 + p2;
                cout << p1 << "\n+\n" << p2 << endl;
                cout << "Результат сложения: " << sum << endl;
                outFile << "Результат сложения: " << sum << endl;
                break;
            }
            case 2: {
                Polynom p1, p2;
                Polynom diff = p1 - p2;
                cout << p1 << "\n-\n" << p2 << endl;
                cout << "Результат вычитания: " << diff << endl;
                outFile << "Результат вычитания: " << diff << endl;
                break;
            }
            case 3: {
                Polynom p1, p2;
                Polynom product = p1 * p2;
                cout << p1 << "\n*\n" << p2 << endl;
                cout << "Результат умножения: " << product << endl;
                outFile << "Результат умножения: " << product << endl;
                break;
            }

            default:
                cout << "Некорректный выбор операции.\n";
                break;
            }
        }
        else if (choice == 2) {
            Polynom p;
            double x;
            cout << p << endl;
            cout << "Введите значение x: ";
            cin >> x;
            p.CalculateValue(x);
        }
        else if (choice == 3) {
            addPolynomsToFile();
        }
        else if (choice == 4) {
            readPolynomsFromFile();
        }
        else if (choice == 5) {
            Polynom p;
            cout << "Результат:\n";
            cout << ++p;
        }
        else if (choice == 6) {
            Polynom p;
            cout << "Результат:\n";
            cout << --p;
        }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "Некорректный выбор пункта меню.\n";
        }

        cout << endl;
    }

    return 0;
}
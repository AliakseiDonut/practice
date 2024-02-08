#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <exception> 
#include <Windows.h>

using namespace std;

string path = "workers.txt";

class Worker {
    string surname;
    string jobTitle;
    int year;
    double salary;

public:
    void fill() {
        cin.ignore();
        cout << "Введите фамилию и инициалы: ";
        getline(cin, surname);
        cout << "Введите должность: ";
        getline(cin, jobTitle);
        cout << "Введите год поступления на работу: ";
        cin >> year;
        cout << "Введите зарплату: ";
        cin >> salary;
    }

    string getSurname() {
        return surname;
    }

    string getJobTitle() {
        return jobTitle;
    }

    int getYear() {
        return year;
    }

    double getSalary() {
        return salary;
    }

    void setSurname(string workerSurname) {
        surname = workerSurname;
    }

    void setJobTitle(string workerJobTitle) {
        jobTitle = workerJobTitle;
    }

    void setYear(int workerYear) {
        year = workerYear;
    }

    void setSalary(double workerSalary) {
        salary = workerSalary;
    }

    void show() {
        ofstream outfile("result.txt", ios::app);
        if (outfile.is_open()) {
            outfile << left << setw(30) << surname;
            outfile << left << setw(30) << jobTitle;
            outfile << left << setw(30) << year;
            outfile << left << setw(30) << salary;
            outfile << endl;
            outfile.close();
        }
        else {
            cout << "Ошибка открытия файла." << endl;
        }

        cout << left << setw(30) << surname;
        cout << left << setw(30) << jobTitle;
        cout << left << setw(30) << year;
        cout << left << setw(30) << salary;
        cout << endl;
    };

    friend ostream& operator<<(ostream& os, const Worker& worker) {
        os << worker.surname << endl;
        os << worker.jobTitle << endl;
        os << worker.year << endl;
        os << worker.salary << endl;
        return os;
    }

    friend istream& operator>>(istream& is, Worker& worker) {
        getline(is >> ws, worker.surname);
        getline(is >> ws, worker.jobTitle);
        is >> worker.year;
        is >> worker.salary;
        return is;
    }
};

void addWorkersToFile() {
    int workersQuantity;
    cout << "Введите количество работников: ";
    cin >> workersQuantity;

    ofstream fout;
    fout.open(path, ofstream::app);

    for (int i = 0; i < workersQuantity; i++) {
        Worker worker;
        worker.fill();
        fout << worker;
    }

    fout.close();
}

void printWorkersList() {
    ifstream fin;
    fin.open(path);

    if (!fin) {
        throw runtime_error("Ошибка открытия файла.");
    }

    Worker worker;
    int workersQuantity = 0;

    while (fin >> worker) {
        workersQuantity++;
    }

    fin.clear();
    fin.seekg(0, ios::beg);

    Worker* workers = nullptr;
    try {
        workers = new Worker[workersQuantity];
    }
    catch (bad_alloc& e) {
        throw runtime_error("Ошибка выделения памяти.");
    }

    for (int i = 0; fin >> workers[i]; i++) {
    }

    fin.close();

    cout << left << setw(30) << "Фамилия и инициалы";
    cout << left << setw(30) << "Должность";
    cout << left << setw(30) << "Год поступления на работу";
    cout << left << setw(30) << "Зарплата";
    cout << endl;

    for (int i = 0; i < workersQuantity; i++) {
        workers[i].show();
    }

    cout << "Выберите список, который хотите вывести" << endl;
    cout << "1 - список работников, стаж работы которых на данном предприятии превышает заданное число лет" << endl;
    cout << "2 - список работников, зарплата которых больше заданной" << endl;
    cout << "3 - список работников, занимающих заданную должность" << endl;

    int menuItem;
    cin >> menuItem;

    bool workersFound = false;

    switch (menuItem) {
    case 1: {
        cout << "Введите стаж работы:";
        int exp;
        cin >> exp;
        cout << left << setw(30) << "Фамилия и инициалы";
        cout << left << setw(30) << "Должность";
        cout << left << setw(30) << "Год поступления на работу";
        cout << left << setw(30) << "Зарплата";
        cout << endl;

        for (int i = 0; i < workersQuantity; i++) {
            if (2023 - workers[i].getYear() > exp) {
                workers[i].show();
                workersFound = true;
            }
        }
        break;
    }
    case 2: {
        cout << "Введите зарплату:";
        double salary;
        cin >> salary;
        cout << left << setw(30) << "Фамилия и инициалы";
        cout << left << setw(30) << "Должность";
        cout << left << setw(30) << "Год поступления на работу";
        cout << left << setw(30) << "Зарплата";
        cout << endl;

        for (int i = 0; i < workersQuantity; i++) {
            if (workers[i].getSalary() > salary) {
                workers[i].show();
                workersFound = true;
            }
        }
        break;
    }
    case 3: {
        cout << "Введите должность:";
        string jobTitle;
        cin >> jobTitle;
        cout << left << setw(30) << "Фамилия и инициалы";
        cout << left << setw(30) << "Должность";
        cout << left << setw(30) << "Год поступления на работу";
        cout << left << setw(30) << "Зарплата";
        cout << endl;

        for (int i = 0; i < workersQuantity; i++) {
            if (workers[i].getJobTitle().compare(jobTitle) == 0) {
                workers[i].show();
                workersFound = true;
            }
        }
        break;
    }

    default:
        cout << "Некорректный ввод" << endl;
    }

    if (!workersFound) {
        cout << "Работники не найдены." << endl;
    }
    delete[] workers;
}

int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (true) {
        cout << "1 - Добавить работников" << endl;
        cout << "2 - Вывести список работников" << endl;
        cout << "3 - Выход" << endl;
        int menuItem;
        cin >> menuItem;

        if (menuItem == 1) {
            try {
                addWorkersToFile();
            }
            catch (const exception& e) {
                cerr << "Ошибка: " << e.what() << endl;
            }
        }
        else if (menuItem == 2) {
            try {
                printWorkersList();
            }
            catch (const exception& e) {
                cerr << "Ошибка: " << e.what() << endl;
            }
        }
        else if (menuItem == 3)
        {
            break;
        }
    }
    return 0;
}
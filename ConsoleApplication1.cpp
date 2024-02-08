#include <iostream> 
#include <string> 
#include <fstream> 
#include <Windows.h> 
#include <iomanip> 

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
        cout << "-----------------------------------------" << endl;
        cout << "Фамилия и инициалы: " << surname << endl;
        cout << "Должность: " << jobTitle << endl;
        cout << "Год поступления на работу: " << year << endl;
        cout << "Зарплата: " << salary << endl;
        cout << "-----------------------------------------" << endl;
    };
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
        fout.write((char*)&worker, sizeof(Worker));
    }

    fout.close();
}

void printWorkersList() {
    ifstream fin;
    fin.open(path);

    Worker worker;
    int workersQuantity = 0;

    while (fin.read((char*)&worker, sizeof(Worker))) {
        workersQuantity++;
    }


    fin.clear();
    fin.seekg(0, ios::beg);

    Worker* workers = new Worker[workersQuantity];
    for (int i = 0; fin.read((char*)&worker, sizeof(Worker)); i++) {
        workers[i] = worker;
    }

    fin.close();

    cout << "Выберите список, который хотите вывести" << endl;
    cout << "1 - список работников, стаж работы которых на данном предприятии превышает заданное число лет" << endl;
    cout << "2 - список работников, зарплата которых больше заданной" << endl;
    cout << "3 - список работников, занимающих заданную должность" << endl;

    int menuItem;
    cin >> menuItem;

    switch (menuItem) {
    case 1:
        cout << "Введите стаж работы:";
        int exp;
        cin >> exp;
        for (int i = 0; i < workersQuantity; i++) {
            if (2023 - workers[i].getYear() > exp) {
                workers[i].show();
            }
        }
        break;
    case 2:
        cout << "Введите зарплату:";
        double salary;
        cin >> salary;
        for (int i = 0; i < workersQuantity; i++) {
            if (workers[i].getSalary() > salary) {
                workers[i].show();
            }
        }
        break;
    case 3:
        cout << "Введите должность:";
        string jobTitle;
        cin >> jobTitle;
        for (int i = 0; i < workersQuantity; i++) {
            if (workers[i].getJobTitle().compare(jobTitle) == 0) {
                workers[i].show();
            }
        }
        break;
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
            addWorkersToFile();
        }
        else if (menuItem == 2) {
            printWorkersList();
        }
        else if (menuItem == 3)
        {
            break;
        }
    }
    return 0;
}
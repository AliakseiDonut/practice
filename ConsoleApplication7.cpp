#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class Student
{
protected:
    string name;
    string surname;
    int age;

public:
    Student(const string& name, const string& surname, int age) : name(name), surname(surname), age(age) {}

    virtual void show()
    {
        cout << "Имя: " << name << endl;
        cout << "Фамилия: " << surname << endl;
        cout << "Возраст: " << age << endl;
    }

    string getName()
    {
        return name;
    }

    void setName(const string& newName)
    {
        name = newName;
    }

    string getSurname()
    {
        return surname;
    }

    void setSurname(const string& newSurname)
    {
        surname = newSurname;
    }

    virtual void displayInfo() = 0;
    virtual string getType() = 0;
    virtual string getInfoString() = 0;
};

class SchoolStudent : public Student
{
private:
    int grade;

public:
    SchoolStudent(const string& name, const string& surname, int age, int grade) : Student(name, surname, age), grade(grade) {}

    void show()
    {
        Student::show();
        cout << "Класс: " << grade << endl;
    }

    void displayInfo()
    {
        cout << "Школьник" << endl;
    }

    string getType()
    {
        return "School";
    }

    string getInfoString()
    {
        return name + "," + surname + "," + to_string(age) + "," + to_string(grade);
    }
};

class CollegeStudent : public Student
{
private:
    string major;

public:
    CollegeStudent(const string& name, const string& surname, int age, const string& major) : Student(name, surname, age), major(major) {}

    void show()
    {
        Student::show();
        cout << "Специальность: " << major << endl;
    }

    void displayInfo()
    {
        cout << "Студент" << endl;
    }

    string getType()
    {
        return "College";
    }

    string getInfoString()
    {
        return name + "," + surname + "," + to_string(age) + "," + major;
    }
};

void addSchoolStudent(vector<Student*>& students)
{
    string name, surname;
    int age, grade;
    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите фамилию: ";
    cin >> surname;
    cout << "Введите возраст: ";
    cin >> age;
    cout << "Введите класс: ";
    cin >> grade;

    students.push_back(new SchoolStudent(name, surname, age, grade));
}

void addCollegeStudent(vector<Student*>& students)
{
    string name, surname, major;
    int age;
    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите фамилию: ";
    cin >> surname;
    cout << "Введите возраст: ";
    cin >> age;
    cout << "Введите специальность: ";
    cin >> major;

    students.push_back(new CollegeStudent(name, surname, age, major));
}

void saveStudentsToFile(const vector<Student*>& students, const string& filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (const auto& student : students)
        {
            file << student->getType() << "," << student->getInfoString() << endl;
        }
        file.close();
        cout << "Students saved to file: " << filename << endl;
    }
    else
    {
        cout << "Unable to open file: " << filename << endl;
    }
}

void loadStudentsFromFile(vector<Student*>& students, const string& filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find(",");
            if (pos != string::npos)
            {
                string type = line.substr(0, pos);
                string data = line.substr(pos + 1);
                pos = data.find(",");
                if (pos != string::npos)
                {
                    string name = data.substr(0, pos);
                    data = data.substr(pos + 1);
                    pos = data.find(",");
                    if (pos != string::npos)
                    {
                        string surname = data.substr(0, pos);
                        data = data.substr(pos + 1);
                        pos = data.find(",");
                        if (pos != string::npos)
                        {
                            int age = stoi(data.substr(0, pos));
                            string extraData = data.substr(pos + 1);
                            if (type == "School")
                            {
                                int grade = stoi(extraData);
                                students.push_back(new SchoolStudent(name, surname, age, grade));
                            }
                            else if (type == "College")
                            {
                                string major = extraData;
                                students.push_back(new CollegeStudent(name, surname, age, major));
                            }
                        }
                    }
                }
            }
        }
        file.close();
        cout << "Students loaded from file: " << filename << endl;
    }
    else
    {
        cout << "Unable to open file: " << filename << endl;
    }
}

void displayAllStudents(const vector<Student*>& students)
{
    cout << "Все учащиеся:" << endl;
    for (const auto& student : students)
    {
        student->show();
        cout << endl;
    }
}

void displayMenu()
{
    cout << "Меню:" << endl;
    cout << "1. Добавить школьного ученика" << endl;
    cout << "2. Добавить студента колледжа" << endl;
    cout << "3. Сохранить учащихся в файл" << endl;
    cout << "4. Загрузить учащихся из файла" << endl;
    cout << "5. Вывести всех учащихся" << endl;
    cout << "6. Выход" << endl;
    cout << "Введите ваш выбор: ";
}

int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Student*> students;

    int choice;
    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addSchoolStudent(students);
            break;
        case 2:
            addCollegeStudent(students);
            break;
        case 3:
            saveStudentsToFile(students, "students.txt");
            break;
        case 4:
            loadStudentsFromFile(students, "students.txt");
            break;
        case 5:
            displayAllStudents(students);
            break;
        case 6:
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
            break;
        }
    } while (choice != 5);

    for (auto& student : students)
    {
        delete student;
    }

    return 0;
}
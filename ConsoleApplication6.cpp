#include <iostream>
#include <sstream>
#include <cmath>
#include <Windows.h>

using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time() : hours(0), minutes(0), seconds(0) {}

    Time(int hours, int minutes, int seconds) : hours(hours), minutes(minutes), seconds(seconds) {}

    Time(const string& timeString) {
        istringstream iss(timeString);
        char delimiter;
        iss >> hours >> delimiter >> minutes >> delimiter >> seconds;
    }

    Time(int totalSeconds) {
        hours = totalSeconds / 3600;
        minutes = (totalSeconds % 3600) / 60;
        seconds = totalSeconds % 60;
    }

    int getTotalSeconds() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    int getTotalMinutes() const {
        return (hours * 60) + minutes;
    }

    int getHours() const {
        return hours;
    }

    int getMinutes() const {
        return minutes;
    }

    int getSeconds() const {
        return seconds;
    }

    Time operator+(int secondsToAdd) const {
        int totalSeconds = getTotalSeconds() + secondsToAdd;
        return Time(totalSeconds);
    }

    Time operator-(int secondsToSubtract) const {
        int totalSeconds = getTotalSeconds() - secondsToSubtract;
        return Time(totalSeconds);
    }

    int operator-(const Time& otherTime) const {
        return getTotalSeconds() - otherTime.getTotalSeconds();
    }

    bool operator==(const Time& otherTime) const {
        return getTotalSeconds() == otherTime.getTotalSeconds();
    }

    bool operator!=(const Time& otherTime) const {
        return getTotalSeconds() != otherTime.getTotalSeconds();
    }

    bool operator<(const Time& otherTime) const {
        return getTotalSeconds() < otherTime.getTotalSeconds();
    }

    bool operator>(const Time& otherTime) const {
        return getTotalSeconds() > otherTime.getTotalSeconds();
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int choice;
    Time t1;
    Time t2;
    int seconds;
    string timeString;
    int diffInSeconds = 0;

    do {
        cout << "Меню:" << endl;
        cout << "1. Создать объект Time с помощью конструктора по умолчанию" << endl;
        cout << "2. Создать объект Time с помощью конструктора с параметрами" << endl;
        cout << "3. Создать объект Time с помощью конструктора из строки" << endl;
        cout << "4. Создать объект Time с помощью конструктора из секунд" << endl;
        cout << "5. Получить общее количество секунд" << endl;
        cout << "6. Получить общее количество минут" << endl;
        cout << "7. Получить часы" << endl;
        cout << "8. Получить минуты" << endl;
        cout << "9. Получить секунды" << endl;
        cout << "10. Сложить время с заданным количеством секунд" << endl;
        cout << "11. Вычесть из времени заданное количество секунд" << endl;
        cout << "12. Вычислить разницу между двумя моментами времени в секундах" << endl;
        cout << "13. Сравнить два момента времени" << endl;
        cout << "0. Выход" << endl;

        cout << "Введите выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            t1 = Time();
            cout << "Объект Time создан с помощью конструктора по умолчанию." << endl;
            break;
        case 2:
            int hours, minutes, seconds;
            cout << "Введите часы: ";
            cin >> hours;
            cout << "Введите минуты: ";
            cin >> minutes;
            cout << "Введите секунды: ";
            cin >> seconds;
            t1 = Time(hours, minutes, seconds);
            cout << "Объект Time создан с помощью конструктора с параметрами." << endl;
            break;
        case 3:
            cin.ignore();
            cout << "Введите время в формате \"часы:минуты:секунды\": ";
            getline(cin, timeString);
            t1 = Time(timeString);
            cout << "Объект Time создан с помощью конструктора из строки." << endl;
            break;
        case 4:
            cout << "Введите количество секунд: ";
            cin >> seconds;
            t1 = Time(seconds);
            cout << "Объект Time создан с помощью конструктора из секунд." << endl;
            break;
        case 5:
            cout << "Общее количество секунд: " << t1.getTotalSeconds() << endl;
            break;
        case 6:
            cout << "Общее количество минут: " << t1.getTotalMinutes() << endl;
            break;
        case 7:
            cout << "Часы: " << t1.getHours() << endl;
            break;
        case 8:
            cout << "Минуты: " << t1.getMinutes() << endl;
            break;
        case 9:
            cout << "Секунды: " << t1.getSeconds() << endl;
            break;
        case 10:
            cout << "Введите количество секунд для сложения: ";
            cin >> seconds;
            t2 = t1 + seconds;
            cout << "Результат сложения: " << t2.getHours() << ":" << t2.getMinutes() << ":" << t2.getSeconds() << endl;
            break;
        case 11:
            cout << "Введите количество секунд для вычитания: ";
            cin >> seconds;
            t2 = t1 - seconds;
            cout << "Результат вычитания: " << t2.getHours() << ":" << t2.getMinutes() << ":" << t2.getSeconds() << endl;
            break;
        case 12:
            cout << "Введите второй момент времени в формате \"часы:минуты:секунды\": ";
            cin.ignore();
            getline(cin, timeString);
            t2 = Time(timeString);
            diffInSeconds = t1 - t2;
            cout << "Разница между моментами времени: " << diffInSeconds << " секунд" << endl;
            break;
        case 13:
            cout << "Введите второй момент времени в формате \"часы:минуты:секунды\": ";
            cin.ignore();
            getline(cin, timeString);
            t2 = Time(timeString);
            if (t1 == t2) {
                cout << "Моменты времени равны." << endl;
            }
            else if (t1 != t2) {
                cout << "Моменты времени не равны." << endl;
            }
            if (t1 < t2) {
                cout << "Первый момент времени меньше второго." << endl;
            }
            else if (t1 > t2) {
                cout << "Первый момент времени больше второго." << endl;
            }
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}
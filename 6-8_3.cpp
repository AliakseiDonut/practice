#include <iostream>
#include <Windows.h>

using namespace std;

class Pair {
protected:
    int first;
    int second;
public:
    Pair(int a, int b) : first(a), second(b) {}

    Pair operator*(int num) {
        return Pair(first * num, second * num);
    }

    Pair operator+(const Pair& other) {
        return Pair(first + other.first, second + other.second);
    }
};

class Money : public Pair {
public:
    Money(int rub, int kop) : Pair(rub, kop) {}

    Money operator+(const Money& other) {
        int rub = first + other.first;
        int kop = second + other.second;
        if (kop >= 100) {
            rub += kop / 100;
            kop %= 100;
        }
        return Money(rub, kop);
    }

    Money operator-(const Money& other) {
        int rub = first - other.first;
        int kop = second - other.second;
        if (kop < 0) {
            rub -= 1;
            kop += 100;
        }
        return Money(rub, kop);
    }

    Money operator/(int num) {
        int rub = first / num;
        int kop = second / num;
        return Money(rub, kop);
    }

    friend ostream& operator<<(ostream& os, const Money& money);
};

ostream& operator<<(ostream& os, const Money& money) {
    os << money.first << " руб. " << money.second << " коп.";
    return os;
}

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Money m1(10, 50);
    Money m2(5, 75);

    Money sum = m1 + m2;
    Money diff = m1 - m2;
    Money div = sum / 3;

    cout << "Сумма: " << sum << endl;
    cout << "Разность: " << diff << endl;
    cout << "Результат деления на 3: " << div << endl;

    return 0;
}
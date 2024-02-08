#include <iostream>
#include <cstring>

class Stroka {
protected:
    int length;

public:
    char* str;

    Stroka() : str(nullptr), length(0) {}

    Stroka(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy_s(str, length + 1, s);
    }

    Stroka(const Stroka& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy_s(str, length + 1, other.str);
    }

    int getLength() const {
        return length;
    }

    void clear() {
        delete[] str;
        str = nullptr;
        length = 0;
    }

    virtual ~Stroka() {
        delete[] str;
    }
};

class BITOVAYA_STROKA : public Stroka {
public:
    BITOVAYA_STROKA() : Stroka() {}

    BITOVAYA_STROKA(const char* s) {
        bool isValid = true;
        for (int i = 0; s[i] != '\0'; i++) {
            if (s[i] != '0' && s[i] != '1') {
                isValid = false;
                break;
            }
        }

        if (isValid) {
            length = strlen(s);
            str = new char[length + 1];
            strcpy_s(str, length + 1, s);
        }
        else {
            str = nullptr;
            length = 0;
        }
    }

    BITOVAYA_STROKA(const BITOVAYA_STROKA& other) : Stroka(other) {}

    ~BITOVAYA_STROKA() {}

    void changeSign() {
        for (int i = 0; i < length; i++) {
            if (str[i] == '0') {
                str[i] = '1';
            }
            else if (str[i] == '1') {
                str[i] = '0';
            }
        }
    }

    BITOVAYA_STROKA& operator=(const BITOVAYA_STROKA& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy_s(str, length + 1, other.str);
        }
        return *this;
    }

    BITOVAYA_STROKA operator+(const BITOVAYA_STROKA& other) {
        int maxLength = std::max(length, other.length);
        char* result = new char[maxLength + 2];
        result[maxLength + 1] = '\0';

        int carry = 0;
        for (int i = maxLength - 1; i >= 0; i--) {
            int sum = (i < length ? str[i] - '0' : 0) + (i < other.length ? other.str[i] - '0' : 0) + carry;
            result[i + 1] = sum % 2 + '0';
            carry = sum / 2;
        }
        result[0] = carry + '0';

        BITOVAYA_STROKA res;
        res.length = maxLength + 1;
        res.str = result;

        return res;
    }

    bool operator==(const BITOVAYA_STROKA& other) const {
        if (length != other.length) {
            return false;
        }
        for (int i = 0; i < length; i++) {
            if (str[i] != other.str[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    BITOVAYA_STROKA a("1010");
    BITOVAYA_STROKA b("1101");
    BITOVAYA_STROKA c("1010");

    BITOVAYA_STROKA d = a + b;

    BITOVAYA_STROKA e = ("hello");

    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a == c: " << (a == c) << std::endl;
    std::cout << "d: " << d.str << std::endl;

    d.changeSign();
    std::cout << "d after changing sign: " << d.str << std::endl;
    d.clear();
    std::cout << "clear: " << d.str << std::endl;
    std::cout << "e:" << e.str << std::endl;
    return 0;
}
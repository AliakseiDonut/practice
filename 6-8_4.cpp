#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Array {
protected:
    char* arr;
public:
    int size;

    Array(int s) : size(s) {
        arr = new char[size];
    }

    virtual ~Array() {
        delete[] arr;
    }

    char& operator[](int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of range" << std::endl;
            exit(1);
        }
        return arr[index];
    }


    virtual Array* add(Array* other) {
        if (size != other->size) {
            throw std::runtime_error("Array sizes are different");
        }

        Array* result = new Array(size);

        for (int i = 0; i < size; ++i) {
            (*result)[i] = arr[i] + (*other)[i];
        }

        return result;
    }
};

class Octal : public Array {
public:
    Octal(int s) : Array(s) {}

    Array* add(Array* other) override {
        Octal* octalOther = dynamic_cast<Octal*>(other);
        if (octalOther == nullptr) {
            std::cerr << "Invalid type for addition" << std::endl;
            exit(1);
        }

        int resultSize = size > octalOther->size ? size : octalOther->size;
        Octal* result = new Octal(resultSize);
        int carry = 0;

        for (int i = resultSize - 1; i >= 0; --i) {
            int num1 = i < size ? arr[i] - '0' : 0;
            int num2 = i < octalOther->size ? octalOther->arr[i] - '0' : 0;
            int sum = num1 + num2 + carry;

            carry = sum / 8;
            sum %= 8;

            if (sum > 7) {
                std::cerr << "Invalid octal digit: " << sum << std::endl;
                exit(1);
            }

            result->arr[i] = sum + '0';
        }

        if (carry > 0) {
            Octal* newResult = new Octal(resultSize + 1);
            if (carry > 7) {
                std::cerr << "Invalid octal digit: " << carry << std::endl;
                exit(1);
            }
            newResult->arr[0] = carry + '0';
            std::memcpy(newResult->arr + 1, result->arr, resultSize);
            delete result;
            result = newResult;
            resultSize++;
        }

        result->size = resultSize;
        return result;
    }
};

class MString : public Array {
public:
    MString(int s) : Array(s) {}

    Array* add(Array* other) override {
        MString* stringOther = dynamic_cast<MString*>(other);
        if (stringOther == nullptr) {
            std::cerr << "Invalid type for addition" << std::endl;
            exit(1);
        }

        int resultSize = size + stringOther->size;
        MString* result = new MString(resultSize);
        std::memcpy(result->arr, arr, size);
        std::memcpy(result->arr + size, stringOther->arr, stringOther->size);
        return result;
    }
};

int main() {
    while (true) {
        int choice;
        std::cout << "Select an option:" << std::endl;
        std::cout << "1. Add octal numbers" << std::endl;
        std::cout << "2. Add strings" << std::endl;
        std::cout << "3. Check indexing" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        try {
            if (choice == 1) {
                int octalSize1, octalSize2;
                std::cout << "Enter the size for the first octal number: ";
                std::cin >> octalSize1;
                std::cout << "Enter the size for the second octal number: ";
                std::cin >> octalSize2;

                Array* arr1 = new Octal(octalSize1);
                std::cout << "Enter the digits for the first octal number (from left to right): ";
                for (int i = 0; i < octalSize1; ++i) {
                    int digit;
                    std::cin >> digit;

                    if (digit < 0 || digit > 7) {
                        throw std::runtime_error("Invalid octal digit: " + std::to_string(digit));
                    }

                    (*arr1)[i] = digit + '0';
                }

                Array* arr2 = new Octal(octalSize2);
                std::cout << "Enter the digits for the second octal number (from left to right): ";
                for (int i = 0; i < octalSize2; ++i) {
                    int digit;
                    std::cin >> digit;

                    if (digit < 0 || digit > 7) {
                        throw std::runtime_error("Invalid octal digit: " + std::to_string(digit));
                    }

                    (*arr2)[i] = digit + '0';
                }

                Array* result = arr1->add(arr2);

                std::cout << "Result of octal addition: ";
                for (int i = 0; i < result->size; ++i) {
                    std::cout << (*result)[i] << " ";
                }
                std::cout << std::endl;

                delete arr1;
                delete arr2;
                delete result;
            }
            else if (choice == 2) {
                int stringSize1, stringSize2;
                std::cout << "Enter the size for the first string: ";
                std::cin >> stringSize1;
                std::cout << "Enter the size for the second string: ";
                std::cin >> stringSize2;

                Array* arr1 = new MString(stringSize1);
                std::cout << "Enter the characters for the first string: ";
                for (int i = 0; i < stringSize1; ++i) {
                    char c;
                    std::cin >> c;
                    (*arr1)[i] = c;
                }

                Array* arr2 = new MString(stringSize2);
                std::cout << "Enter the characters for the second string: ";
                for (int i = 0; i < stringSize2; ++i) {
                    char c;
                    std::cin >> c;
                    (*arr2)[i] = c;
                }

                Array* result = arr1->add(arr2);

                std::cout << "Result of string addition: ";
                for (int i = 0; i < result->size; ++i) {
                    std::cout << (*result)[i];
                }
                std::cout << std::endl;

                delete arr1;
                delete arr2;
                delete result;
            }
            else if (choice == 3) {
                int index, size;
                std::cout << "Enter the size of the array: ";
                std::cin >> size;

                Array* arr = new Array(size);
                std::cout << "Enter the elements of the array: ";
                for (int i = 0; i < size; ++i) {
                    char element;
                    std::cin >> element;
                    (*arr)[i] = element;
                }

                std::cout << "Enter the index to check: ";
                std::cin >> index;

                try {
                    char& value = (*arr)[index];
                    std::cout << "Value at index " << index << ": " << value << std::endl;
                }
                catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }

            }
            else if (choice == 4) {
                std::cout << "Exiting the program." << std::endl;
                break;  // Exit the loop and end the program.
            }
            else {
                throw std::runtime_error("Invalid choice");
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
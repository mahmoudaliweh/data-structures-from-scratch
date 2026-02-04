#include <iostream>
using namespace std;

class Array {
private:
    int *array;
    int capacity;
    int size;

public:
    Array(int capacity = 10): capacity(capacity), size(0) {
        array = new int[this->capacity];
    }

    ~Array() {
        delete[] array;
    }

    void addElement(int element) {
        if (size == capacity) {
            int *newArray = new int[size + 1];
            for (int i = 0; i < size; i++) {
                newArray[i] = array[i];
            }
            newArray[size] = element;
            delete[] array;
            array = newArray;
            size++;
            capacity++;
            return;
        }
        array[size] = element;
        size++;
    }

    void getArrayInfo() {
        cout << "Array capacity: " << capacity << endl;
        cout << "Array size: " << size << endl;
        cout << "Array contents: ";
        for (int i = 0; i < size; i++) {
            cout << array[i] << ' ';
        }
        cout << endl;
    }
};

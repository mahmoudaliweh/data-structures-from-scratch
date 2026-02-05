#include <iostream>
using namespace std;

class DynamicArray {
private:
    int capcaity;
    int size;
    int *buffer;

public:
    DynamicArray(int initialCapacity) : capcaity(initialCapacity), size(0), buffer(new int[capcaity]) {
    }

    ~DynamicArray() {
        delete[] buffer;
    }

    void resize(int newCapacity) {
        int *newBuffer = new int[newCapacity];
        for (int i = 0; i < size; i++) {
            newBuffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = newBuffer;
        capcaity = newCapacity;
    }

    void push_back(int element) {
        if (size >= capcaity) {
            resize(capcaity * 2);
        } else {
            buffer[size] = element;
            size++;
        }
    }

    void pop_back() {
        if (size == 0) {
            cout << "Array is alreayd empty!" << endl;
            return;
        }
        size--;
    }
};

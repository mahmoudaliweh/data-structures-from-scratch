#include <iostream>
using namespace std;

class Deque {
private:
    int capacity;
    int size;
    int *circular_buffer;
    int front_index;
    int back_index;

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }

public:
    Deque(int cap): capacity(cap), front_index(0), back_index(0), size(0) {
        circular_buffer = new int[capacity];
    }

    ~Deque() {
        delete[] circular_buffer;
    }


    void insert_front(int value) {
        if (isEmpty()) {
            circular_buffer[front_index] = value;
            size++;
            return;
        }
        if (isFull()) {
            cout << "Deque is full" << endl;
            return;
        }
        front_index--;
        if (front_index < 0) front_index += capacity;
        circular_buffer[front_index] = value;
        size++;
    }

    void insert_back(int value) {
        if (isEmpty()) {
            circular_buffer[back_index] = value;
            size++;
            return;
        }
        if (isFull()) {
            cout << "Deque is full" << endl;
            return;
        }
        back_index = (back_index + 1) % capacity;
        circular_buffer[back_index] = value;
        size++;
    }

    void delete_front() {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return;
        }
        cout << "Deleting: " << circular_buffer[front_index] << endl;
        size--;
        if (size == 0) {
            front_index = back_index = 0;
            return;
        }

        front_index++;
        front_index %= capacity;
    }

    void delete_back() {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return;
        }
        cout << "Deleting: " << circular_buffer[back_index] << endl;
        size--;
        if (size == 0) {
            front_index = back_index = 0;
            return;
        }
        back_index--;
        if (back_index < 0) {
            back_index += capacity;
        }
    }

    void print() {
        int current = front_index;
        for (int i = 0; i < size; i++) {
            cout << circular_buffer[current] << ' ';
            current = (current + 1) % capacity;
        }
        cout << endl;
    }
};

int main() {
    Deque list(10);
    list.insert_front(2);
    list.print();
    list.insert_front(6);
    list.print();
    list.insert_front(9);
    list.print();
    list.insert_back(12);
    list.print();
    list.insert_back(54);
    list.print();
    list.delete_back();
    list.print();
    list.delete_front();
    list.print();
    return 0;
}

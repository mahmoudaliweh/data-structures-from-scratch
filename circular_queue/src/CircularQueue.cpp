#include <iostream>
#include <ranges>
using namespace std;

class CircularQueue {
private:
    int capacity;
    int size;
    int front;
    int *buffer;

public:
    CircularQueue(int cap): capacity(cap), size(0), front(0), buffer(new int[capacity]) {
    }

    ~CircularQueue() {
        delete[] buffer;
    }


    void enqueue(int value) {
        if (size == capacity) {
            cout << "Queue is full" << endl;
            return;
        }
        buffer[(front + size) % capacity] = value;
        size++;
    }

    void dequeue() {
        if (size == 0) {
            cout << "Queue is empty" << endl;
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }
};

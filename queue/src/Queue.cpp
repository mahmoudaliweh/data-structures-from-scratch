#include <iostream>
using namespace std;

class Node {
private:
    int data;
    Node *next;
    friend class Queue;

public:
    Node(int value): data(value), next(nullptr) {
    }
};

class Queue {
private:
    Node *front;
    Node *back;

public:
    Queue(): front(nullptr), back(nullptr) {
    }

    ~Queue() {
        Node *current = front;
        while (current) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    void enqueue(int value) {
        Node *newNode = new Node(value);
        if (!back) {
            back = newNode;
            front = newNode;
            return;
        }
        back->next = newNode;
        back = newNode;
    }

    void dequeue() {
        if (!front) {
            cout << "Queue is empty" << endl;
            return;
        }
        Node *toDelete = front;
        front = front->next;
        if (!front) {
            back = nullptr;
        }
        delete toDelete;
    }

    void print() {
        if (!front) {
            cout << "Queue is empty" << endl;
            return;
        }
        Node *current = front;
        while (current) {
            cout << current->data << ' ';
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    Queue myQ;
    myQ.enqueue(1);
    myQ.enqueue(2);
    myQ.enqueue(3);
    myQ.print();
    myQ.dequeue();
    myQ.print();
    myQ.dequeue();
    myQ.dequeue();
    myQ.dequeue();
    myQ.print();
    return 0;
}

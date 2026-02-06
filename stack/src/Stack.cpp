#include <iostream>
using namespace std;

class Node {
private:
    int data;
    Node *next;
    friend class Stack;

public:
    Node(int value): data(value), next(nullptr) {
    }
};

class Stack {
private:
    Node *top;

public:
    Stack(): top(nullptr) {
    }

    ~Stack() {
        Node *current = top;
        while (current) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    void push(int value) {
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!top) {
            return;
        }
        Node *nodeToDelete = top;
        top = top->next;
        delete nodeToDelete;
    }

    int peek() {
        if (!top) {
            return -1;
        }
        return top->data;
    }
};

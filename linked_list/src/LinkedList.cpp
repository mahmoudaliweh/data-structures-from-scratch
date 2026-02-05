#include <iostream>
using namespace std;

class Node {
private:
    int data;
    Node *next;

public:
    Node(int data): data(data), next(nullptr) {
    }

    void setNext(Node *next) {
        this->next = next;
    }

    Node *getNext() {
        return next;
    }

    const int &getData() {
        return data;
    }
};

class LinkedList {
private:
    Node *head;

public:
    LinkedList(): head(nullptr) {
    }

    ~LinkedList() {
        Node *current = head;
        while (current) {
            Node *toDelete = current;
            current = current->getNext();
            delete toDelete;
        }
    }

    void insert_front(int value) {
        Node *nodeToInsert = new Node(value);
        nodeToInsert->setNext(head);
        head = nodeToInsert;
    }

    void insert_back(int value) {
        Node *newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node *current = head;
        while (current->getNext()) {
            current = current->getNext();
        }
        current->setNext(newNode);
    }

    bool delete_value(int value) {
        Node* current = head;
        Node* prev = nullptr;
        while (current) {
            if(current->getData() == value) {
                if(prev) {
                    prev->setNext(current->getNext());
                    delete current;
                } else {
                    head = current->getNext();
                    delete current;
                }
                return true;
            } else {
                prev = current;
                current = current->getNext();
            }
        }

        return false;
    }
};

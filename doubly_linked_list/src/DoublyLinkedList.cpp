#include <iostream>
using namespace std;

class Node {
private:
    int data;
    Node *next;
    Node *prev;
    friend class DoublyLinkedList;

public:
    Node(): next(nullptr), prev(nullptr) {
    }

    Node(int value): data(value), next(nullptr), prev(nullptr) {
    }
};

class DoublyLinkedList {
private:
    Node *head;
    Node *tail;

public:
    DoublyLinkedList(): head(nullptr), tail(nullptr) {
    }

    ~DoublyLinkedList() {
        Node *current = head;
        while (current) {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    void insert_front(int value) {
        Node *newNode = new Node(value);
        newNode->next = head;
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
    }

    void insert_back(int value) {
        Node *newNode = new Node(value);
        newNode->prev = tail;
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
    }

    void delete_node(Node *nodeToDelete) {
        if (!nodeToDelete) return;
        if (nodeToDelete->prev) {
            nodeToDelete->prev->next = nodeToDelete->next;
        } else {
            head = nodeToDelete->next;
        }
        if (nodeToDelete->next) {
            nodeToDelete->next->prev = nodeToDelete->prev;
        } else {
            tail = nodeToDelete->prev;
        }

        delete nodeToDelete;
    }
};

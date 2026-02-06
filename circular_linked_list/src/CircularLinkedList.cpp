#include <iostream>
using namespace std;

class Node {
    int data;
    Node *next;
    friend class CircularLinkedList;
    Node(int value): data(value), next(nullptr){}
};

class CircularLinkedList {
private:
    Node *cursor;
public:
    CircularLinkedList(): cursor(nullptr){}
    ~CircularLinkedList() {
        if(!cursor) return;
        Node *current = cursor->next;
        while (current != cursor) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        delete cursor;

    }
    void insert_front(int value) {
        Node *newNode = new Node(value);
        if(!cursor) {
            cursor = newNode;
            newNode->next = newNode;
            return;
        }
        newNode->next = cursor->next;
        cursor->next = newNode;
    }

    void advance_cursor() {
        if(cursor) {
            cursor = cursor->next;
        }
    }

    void insert_back(int value) {
        Node *newNode = new Node(value);
        if(!cursor) {
            cursor = newNode;
            newNode->next = newNode;
            return;
        }
        newNode->next = cursor->next;
        cursor->next = newNode;
        advance_cursor();
    }

    void delete_front() {
        if(!cursor) {
            cout << "List is empty" << endl;
            return;
        }
        if(cursor == cursor->next) {
            delete cursor;
            cursor = nullptr;
            return;
        }
        Node *toDelete = cursor->next;
        cursor->next = toDelete->next;
        delete toDelete;
    }

    void delete_back() { // would be O(n)
        if(!cursor) {
            cout << "List is empty" << endl;
            return;
        }
    }

    void print() {
        if(!cursor) {
            cout << "Empty list" << endl;
            return;
        }
        Node *current = cursor->next;
        while (current != cursor) {
            cout << current->data << ' ';
            current = current->next;
        }
        cout << current->data << endl;
    }
};

int main() {
    CircularLinkedList list;
    list.insert_front(2);
    list.insert_front(6);
    list.print();
    // 6 2
    list.insert_back(5);
    list.insert_back(9);
    list.print();
    // 6 2 5 9
    list.advance_cursor();
    list.print();
    // 2 5 9 6
    list.delete_front();
    list.print();
    list.delete_front();
    list.print();
    list.delete_front();
    list.print();
    list.delete_front();
    list.print();


}


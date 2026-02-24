#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

class Node {
private:
    Node **next;
    int key;
    friend class SkipList;

public:
    Node(int key, int levels) {
        this->key = key;
        next = new Node *[levels + 1];
        for (int i = 0; i < levels; i++) {
            next[i] = nullptr;
        }
    }
    ~Node() {
        delete[] next;
    }
};

class SkipList {
private:
    Node *header;
    int max_level;
    int level;

    int randomLevel() {
        int lvl = 0;
        while (((float) rand() / RAND_MAX) < 0.5 && lvl < max_level)
            lvl++;
        return lvl;
    }

public:
    SkipList(int maxLevel) {
        max_level = maxLevel;
        header = new Node(INT_MIN, max_level);
        level = 0;
        srand((unsigned) time(0));
    }
    ~SkipList() {
        Node* current = header->next[0];
        while (current != nullptr) {
            Node* temp = current->next[0];
            delete current;
            current = temp;
        }
        delete header;
    }

    bool search(int key) {
        Node *current = header;
        int currentLevel = level;
        while (currentLevel >= 0) {
            if (!current->next[currentLevel] || current->next[currentLevel]->key > key) {
                currentLevel--;
            } else if (current->next[currentLevel]->key < key) {
                current = current->next[currentLevel];
            } else {
                return true;
            }
        }
        return false;
    }

    void insert(int key) {
        Node *update[max_level + 1];
        Node *current = header;

        for (int i = level; i >= 0; i--) {
            while (current->next[i] && current->next[i]->key < key) {
                current = current->next[i];
            }
            update[i] = current;
        }

        current = current->next[0];

        if (current == nullptr || current->key != key) {
            int rlevel = randomLevel();
            if (rlevel > level) {
                for (int i = level + 1; i <= rlevel; i++)
                    update[i] = header;
                level = rlevel;
            }
            Node* n = new Node(key, level);
            for (int i = 0; i <= rlevel; i++) {
                n->next[i] = update[i]->next[i];
                update[i]->next[i] = n;
            }
        }
    }

    void display() {
        cout << "\n***** Skip List *****\n";
        for (int i = 0; i <= level; i++) {
            Node* node = header->next[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->key << " ";
                node = node->next[i];
            }
            cout << "\n";
        }
    }
};



#include <iostream>
using namespace std;

class Node {
private:
    Node *children[26];
    bool isEnd;
    friend class Trie;

public:
    Node() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        isEnd = false;
    }

    bool exists(char c) {
        return (children[c - 'a'] != nullptr);
    }

    void insert(char c) {
        children[c - 'a'] = new Node;
    }
};

class Trie {
private:
    Node *root;

    bool deleteWord(Node *node, const string &word, int index) {
        if (!node) {
            return false;
        }
        if (index < word.length()) {
            if (node->exists(word[index])) {
                if (deleteWord(node->children[word[index] - 'a'], word, index + 1)) {
                    delete node->children[word[index] - 'a'];
                    node->children[word[index] - 'a'] = nullptr;
                    return isEmpty(node) && !node->isEnd;
                } else return false;
            } else {
                return false;
            }
        } else {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return isEmpty(node);
        }
    }

    bool isEmpty(Node *node) {
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) return false;
        }
        return true;
    }


    void clear(Node *node) {
        if (!node) return;
        for (int i = 0; i < 26; i++) {
            clear(node->children[i]);
        }
        delete node;
    }

public:
    Trie() {
        root = new Node;
    }

    ~Trie() {
        clear(root);
    }

    void Insert(const string &word) {
        Node *current = root;

        for (char c: word) {
            if (!current->exists(c)) {
                current->insert(c);
            }
            current = current->children[c - 'a'];
        }

        current->isEnd = true;
    }

    void Delete(const string &word) {
        deleteWord(root, word, 0);
    }
};

#include <iostream>
using namespace std;

enum class COLOR { RED, BLACK };

class Node {
private:
    COLOR color;
    int key;
    Node *left;
    Node *right;
    Node *parent;
    friend class RedBlackTree;

public:
    Node(int key): key(key), color(COLOR::RED), left(nullptr), right(nullptr), parent(nullptr) {
    }
};

class RedBlackTree {
private:
    Node *root;

    bool isBlack(Node *node) {
        if (!node || node->color == COLOR::BLACK) {
            return true;
        }
        return false;
    }

    bool isRed(Node *node) {
        return !isBlack(node);
    }

    void leftRotate(Node *node) {
        Node *x = node;
        Node *y = node->right;
        Node *xParent = x->parent;
        if (xParent) {
            if (isALeftChild(x)) {
                xParent->left = y;
            } else {
                xParent->right = y;
            }
        } else {
            root = y;
        }
        y->parent = xParent;
        x->right = y->left;
        if (y->left) {
            y->left->parent = x;
        }
        x->parent = y;
        y->left = x;
    }

    void rightRotate(Node *node) {
        Node *x = node;
        Node *y = node->left;
        Node *xParent = x->parent;
        if (xParent) {
            if (isALeftChild(x)) {
                xParent->left = y;
            } else {
                xParent->right = y;
            }
        } else {
            root = y;
        }
        y->parent = xParent;
        x->left = y->right;
        if (y->right) {
            y->right->parent = x;
        }
        x->parent = y;
        y->right = x;
    }

    Node *parent(Node *node) {
        if (node) {
            return node->parent;
        }
        return nullptr;
    }

    Node *grandparent(Node *node) {
        if (parent(node)) {
            return node->parent->parent;
        }
        return nullptr;
    }

    Node *uncle(Node *node) {
        if (grandparent(node)) {
            return (node->parent == node->parent->parent->left
                        ? node->parent->parent->right
                        : node->parent->parent->left);
        }
        return nullptr;
    }

    bool isALeftChild(Node *node) {
        return node && node->parent && node == node->parent->left;
    }

    bool isARightChild(Node *node) {
        return !isALeftChild(node);
    }


    void fix(Node *node) {
        if (node == root) {
            node->color = COLOR::BLACK;
            return;
        }
        Node *p = parent(node);
        Node *g = grandparent(node);
        if (isRed(node->parent)) {
            if (isRed(uncle(node))) {
                uncle(node)->color = COLOR::BLACK;
                parent(node)->color = COLOR::BLACK;
                grandparent(node)->color = COLOR::RED;
                fix(grandparent(node));
                return;
            }
            if (isARightChild(p)) {
                if (isALeftChild(node)) {
                    rightRotate(p);
                }
                g->color = COLOR::RED;
                g->right->color = COLOR::BLACK;
                leftRotate(g);
            } else {
                if (isARightChild(node)) {
                    leftRotate(p);
                }
                g->color = COLOR::RED;
                g->left->color = COLOR::BLACK;
                rightRotate(g);
            }
        }
        root->color = COLOR::BLACK;
    }

public:
    RedBlackTree(): root(nullptr) {
    }

    void insert(int key) {
        Node *node = new Node(key);
        Node *current = root;
        Node *parent = nullptr;
        while (current) {
            parent = current;
            if (key > current->key) {
                current = current->right;
            } else if (key < current->key) {
                current = current->left;
            } else {
                delete node;
                return;
            }
        }
        if (parent) {
            node->parent = parent;
            if (key > parent->key) {
                parent->right = node;
            } else {
                parent->left = node;
            }
        } else {
            root = node;
        }
        fix(node);
    }
};

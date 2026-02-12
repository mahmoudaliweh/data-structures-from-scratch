#include <iostream>
using namespace std;

enum class COLOR {RED, BLACK};
class Node {
private:
    COLOR color;
    int key;
    Node* left;
    Node* right;
    Node* parent;
    friend class RedBlackTree;

public:
    Node(int key):key(key), color(COLOR::RED), left(nullptr), right(nullptr), parent(nullptr){}
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;
    bool isBlack(Node* node) {
        return node->color == COLOR::BLACK;
    }
    bool isRed(Node* node) {
        return !isBlack(node);
    }
    Node* parent(Node* node) {
        return node->parent;
    }
    Node* uncle(Node* node) {
        return (node->parent->parent->right == node->parent ? node->parent->parent->left:node->parent->parent->right);
    }
    Node* grandparent(Node* node) {
        return node->parent->parent;
    }
    bool isALeftChild(Node* node) {
        return parent(node)->left == node;
    }
    bool isARightChild(Node* node) {
        return !isALeftChild(node);
    }
    void leftRotate(Node* x) {
        Node* y = x->right;

        x->right = y->left;

        if (y->left != NIL)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;  // x will become new parent

        // Move x's right subtree to y's left
        y->left = x->right;
        if (x->right != NIL)
            x->right->parent = y;

        // Link x to y's parent
        x->parent = y->parent;
        if (y->parent == NIL)
            root = x; // Update root if y was root
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        // Put y as right child of x
        x->right = y;
        y->parent = x;
    }


    void fix(Node* node) {
        if(node == root) {
            node->color = COLOR::BLACK;
            return;
        }
        if(isBlack(parent(node))) {
            return;
        }
        if(isRed(uncle(node))) {
            parent(node)->color = COLOR::BLACK;
            uncle(node)->color = COLOR::BLACK;
            grandparent(node)->color = COLOR::RED;
            fix(grandparent(node));
            return;
        }
        if(isARightChild(node)) {
            if(isALeftChild(parent(node))) {
                rightRotate(parent(node));
            }
            grandparent(node)->color = COLOR::RED;
            parent(node)->color = COLOR::BLACK;
            leftRotate(grandparent(node));
        } else {
            if(isARightChild(parent(node))) {
                leftRotate(parent(node));
            }
            grandparent(node)->color = COLOR::RED;
            parent(node)->color = COLOR::BLACK;
            rightRotate(grandparent(node));
        }

    }

    Node* createNode(int key) {
        Node* node = new Node(key);
        node->left = NIL;
        node->right = NIL;
        node->color = COLOR::RED;
        return node;
    }
public:
    RedBlackTree() {
        NIL = new Node(0);
        NIL->color = COLOR::BLACK;
        NIL->right = NIL;
        NIL->left = NIL;
        NIL->parent = nullptr;
        root = NIL;
    }
    void Insert(int key) {
        Node* node = createNode(key);
        if(root == NIL) {
            root = node;
            node->color = COLOR::BLACK;
            return;
        }
        Node* current = root;
        Node* parent = nullptr;
        while (current != NIL) {
            parent = current;
            if(key > current->key) {
                current = current->right;
            } else if(key < current->key) {
                current = current->left;
            } else {
                delete node;
                return;
            }
        }
        node->parent = parent;
        if(key > parent->key) {
            parent->right = node;
        } else {
            parent->left = node;
        }
        fix(node);
    }
};
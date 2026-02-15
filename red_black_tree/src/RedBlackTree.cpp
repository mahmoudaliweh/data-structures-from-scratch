#include <iostream>
using namespace std;

enum class COLOR { RED, BLACK, NIL };

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
        return node && node->parent && node == node->parent->right;
    }


    void insertFix(Node *node) {
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
                insertFix(grandparent(node));
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

    void doubleBlack(Node *node) {
        if (node == root) {
            node->color = COLOR::BLACK;
        } else if (isALeftChild(node)) {
            if (node->parent->right && isRed(node->parent->right)) {
                node->parent->color = COLOR::RED;
                node->parent->right->color = COLOR::BLACK;
                leftRotate(node->parent);
                doubleBlack(node);
            } else if (isRed(node->parent->right->right)) {
                node->parent->right->color = node->parent->color;
                node->parent->color = COLOR::BLACK;
                node->parent->right->right->color = COLOR::BLACK;
                leftRotate(node->parent);
                if (node->color == COLOR::NIL) {
                    deleteNode(node);
                }
            } else if (isRed(node->parent)) {
                node->parent->color = COLOR::BLACK;
                node->parent->right->color = COLOR::RED;
                if (node->color == COLOR::NIL) {
                    deleteNode(node);
                }
            } else if (isRed(node->parent->right->left)) {
                node->parent->right->color = COLOR::RED;
                node->parent->right->left->color = COLOR::BLACK;
                leftRotate(node->parent->right);
                doubleBlack(node);
            } else {
                node->parent->right->color = COLOR::RED;
                Node *nextDB = node->parent;
                if (node->color == COLOR::NIL) {
                    deleteNode(node);
                }
                doubleBlack(nextDB);
            }
        } else if (isARightChild(node)) {
            if (node->parent->left && isRed(node->parent->left)) {
                node->parent->color = COLOR::RED;
                node->parent->left->color = COLOR::BLACK;
                rightRotate(node->parent);
                doubleBlack(node);
            } else if (isRed(node->parent->left->left)) {
                node->parent->left->color = node->parent->color;
                node->parent->color = COLOR::BLACK;
                node->parent->left->left->color = COLOR::BLACK;
                rightRotate(node->parent);
                if (node->color == COLOR::NIL) {
                    deleteNode(node);
                }
            } else if (isRed(node->parent)) {
                node->parent->color = COLOR::BLACK;
                node->parent->left->color = COLOR::RED;
                if (node->color == COLOR::NIL) {
                    deleteNode(node);
                }
            } else if (isRed(node->parent->left->right)) {
                node->parent->left->color = COLOR::RED;
                node->parent->left->right->color = COLOR::BLACK;
                rightRotate(node->parent->left);
                doubleBlack(node);
            } else {
                node->parent->left->color = COLOR::RED;
                Node *nextDB = node->parent;
                if (node->color == COLOR::NIL) {
                    deleteNode(node);
                }
                doubleBlack(nextDB);
            }
        }
    }

    void deleteNode(Node *node) {
        if (isALeftChild(node)) {
            node->parent->left = nullptr;
        }
        if (isARightChild(node)) {
            node->parent->right = nullptr;
        }
        if (node->right) {
            node->right->parent = nullptr;
        }
        if (node->left) {
            node->left->parent = nullptr;
        }
        delete node;
    }

    Node *inOrderSuccessor(Node *node) {
        Node *current = node->right;
        while (true) {
            if (current->left) {
                current = current->left;
            } else {
                break;
            }
        }
        return current;
    }

    Node *inOrderPredecessor(Node *node) {
        Node *current = node->left;
        while (true) {
            if (current->right) {
                current = current->right;
            } else {
                break;
            }
        }
        return current;
    }

    bool isLeaf(Node *node) {
        if (node) {
            return (!node->right && !node->left);
        }
        return false;
    }

public:
    RedBlackTree(): root(nullptr) {
    }

    void Insert(int key) {
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
        insertFix(node);
    }
    
    
    void Delete(int key) {
        Node *current = root;
        while (current) {
            if (key > current->key) {
                current = current->right;
            } else if (key < current->key) {
                current = current->left;
            } else {
                if (isLeaf(current)) {
                    if (isRed(current)) {
                        deleteNode(current);
                    } else {
                        if (current == root) {
                            delete root;
                            root = nullptr;
                        } else {
                            current->color = COLOR::NIL;
                            doubleBlack(current);
                        }
                    }
                    return;
                }

                if (current->right && current->left) {
                    Node *successor = inOrderPredecessor(current);
                    current->key = successor->key;
                    key = successor->key;
                    current = successor;
                    continue;
                }

                if (current->right) {
                    current->right->color = COLOR::BLACK;
                    current->right->parent = current->parent;
                    if (isALeftChild(current)) {
                        current->parent->left = current->right;
                    } else if (isARightChild(current)) {
                        current->parent->right = current->right;
                    } else {
                        root = current->right;
                    }
                    delete current;
                    return;
                }

                if (current->left) {
                    current->left->color = COLOR::BLACK;
                    current->left->parent = current->parent;
                    if (isALeftChild(current)) {
                        current->parent->left = current->left;
                    } else if (isARightChild(current)) {
                        current->parent->right = current->left;
                    } else {
                        root = current->left;
                    }
                    delete current;
                    return;
                }
            }
        }
    }
};




#include <iostream>
using namespace std;

class Node {
private:
    int key;
    Node *leftChild;
    Node *rightChild;
    int height;
    friend class AVLTree;

public:
    Node(int key): key(key), leftChild(nullptr), rightChild(nullptr), height(0) {
    }
};

class AVLTree {
private:
    Node *root;

    void updateHeight(Node *node) {
        int leftHeight = (node->leftChild ? node->leftChild->height : -1);
        int rightHeight = (node->rightChild ? node->rightChild->height : -1);
        node->height = max(leftHeight, rightHeight) + 1;
    }

    int getBalance(Node *node) {
        int leftHeight = (node->leftChild ? node->leftChild->height : -1);
        int rightHeight = (node->rightChild ? node->rightChild->height : -1);
        return leftHeight - rightHeight;
    }

    Node *leftRotate(Node *node) {
        Node *oldRightChild = node->rightChild;
        node->rightChild = oldRightChild->leftChild;
        oldRightChild->leftChild = node;
        updateHeight(node);
        updateHeight(oldRightChild);
        return oldRightChild;
    }

    Node *rightRotate(Node *node) {
        Node *oldLeftChild = node->leftChild;
        node->leftChild = oldLeftChild->rightChild;
        oldLeftChild->rightChild = node;
        updateHeight(node);
        updateHeight(oldLeftChild);
        return oldLeftChild;
    }

    Node *balance(Node *node) {
        int balanceFactor = getBalance(node);
        if (balanceFactor < -1) {
            if (getBalance(node->rightChild) > 0) {
                node->rightChild = rightRotate(node->rightChild);
            }
            return leftRotate(node);
        }
        if (balanceFactor > 1) {
            if (getBalance(node->leftChild) < 0) {
                node->leftChild = leftRotate(node->leftChild);
            }
            return rightRotate(node);
        }
        return node;
    }


    Node *insertNode(int key, Node *currentNode) {
        if (key > currentNode->key) {
            if (currentNode->rightChild == nullptr) {
                currentNode->rightChild = new Node(key);
            } else {
                currentNode->rightChild = insertNode(key, currentNode->rightChild);
            }
        } else if (key < currentNode->key) {
            if (currentNode->leftChild == nullptr) {
                currentNode->leftChild = new Node(key);
            } else {
                currentNode->leftChild = insertNode(key, currentNode->leftChild);
            }
        } else return currentNode;

        updateHeight(currentNode);
        return balance(currentNode);
    }

    void inOrderTraversal(Node *currentNode) {
        if (!currentNode) return;
        inOrderTraversal(currentNode->leftChild);
        cout << "key: " << currentNode->key << " Balance: " << getBalance(currentNode) << endl;
        inOrderTraversal(currentNode->rightChild);
    }

    Node *replaceWithInOrderSuccessor(Node *node, Node *currentNode) {
        if (!currentNode->leftChild) {
            node->key = currentNode->key;
            Node *rightChild = currentNode->rightChild;
            delete currentNode;
            return rightChild;
        }
        currentNode->leftChild = replaceWithInOrderSuccessor(node, currentNode->leftChild);
        updateHeight(currentNode);
        return balance(currentNode);
    }

    Node *deleteNode(int key, Node *currentNode) {
        if (!currentNode) {
            return nullptr;
        }
        if (key == currentNode->key) {
            if (currentNode->rightChild && currentNode->leftChild) {
                currentNode->rightChild = replaceWithInOrderSuccessor(currentNode, currentNode->rightChild);
            } else if (currentNode->rightChild) {
                Node *rightChild = currentNode->rightChild;
                delete currentNode;
                return rightChild;
            } else if (currentNode->leftChild) {
                Node *leftChild = currentNode->leftChild;
                delete currentNode;
                return leftChild;
            } else {
                delete currentNode;
                return nullptr;
            }
        } else if (key > currentNode->key) {
            currentNode->rightChild = deleteNode(key, currentNode->rightChild);
        } else if (key < currentNode->key) {
            currentNode->leftChild = deleteNode(key, currentNode->leftChild);
        }
        updateHeight(currentNode);
        return balance(currentNode);
    }

    Node *search(int key, Node *currentNode) {
        if (!currentNode) {
            return nullptr;
        }
        if (currentNode->key == key) {
            return currentNode;
        } else if (key > currentNode->key) {
            return search(key, currentNode->rightChild);
        } else {
            return search(key, currentNode->leftChild);
        }
    }

public:
    AVLTree(): root(nullptr) {
    }

    void Insert(int key) {
        if (!root) {
            root = new Node(key);
            return;
        }
        root = insertNode(key, root);
    }

    void Delete(int key) {
        root = deleteNode(key, root);
    }

    Node *Search(int key) {
        return search(key, root);
    }

    void Print() {
        if (!root) {
            cout << "Tree is empty" << endl;
            return;
        }
        inOrderTraversal(root);
        cout << endl;
    }
};

#include <iostream>
using namespace std;

class Node {
private:
    int data;
    Node *leftChild;
    Node *rightChild;
    int height;
    friend class AVLTree;

public:
    Node(int data): data(data), leftChild(nullptr), rightChild(nullptr), height(0) {
    }
};

class AVLTree {
private:
    Node *root;

    void updateHeight(Node* node) {
        int leftHeight = (node->leftChild? node->leftChild->height: -1);
        int rightHeight = (node->rightChild? node->rightChild->height: -1);
        node->height = max(leftHeight, rightHeight) + 1;
    }

    int getBalance(Node* node) {
        int leftHeight = (node->leftChild? node->leftChild->height: -1);
        int rightHeight = (node->rightChild? node->rightChild->height: -1);
        return leftHeight - rightHeight;
    }
    Node *leftRotate(Node* node) {
        Node* oldRightChild = node->rightChild;
        node->rightChild = oldRightChild->leftChild;
        oldRightChild->leftChild = node;
        updateHeight(node);
        updateHeight(oldRightChild);
        return oldRightChild;
    }

    Node *rightRotate(Node* node) {
        Node* oldLeftChild = node->leftChild;
        node->leftChild = oldLeftChild->rightChild;
        oldLeftChild->rightChild = node;
        updateHeight(node);
        updateHeight(oldLeftChild);
        return oldLeftChild;
    }


    Node *insertNode(Node *nodeToInsert, Node *nodeToInsertIn) {
        if (nodeToInsert->data > nodeToInsertIn->data) {

            if (nodeToInsertIn->rightChild == nullptr) {
                nodeToInsertIn->rightChild = nodeToInsert;

            } else {
                nodeToInsertIn->rightChild = insertNode(nodeToInsert, nodeToInsertIn->rightChild);

            }

        } else if (nodeToInsert->data < nodeToInsertIn->data) {

            if (nodeToInsertIn->leftChild == nullptr) {
                nodeToInsertIn->leftChild = nodeToInsert;

            } else {
                nodeToInsertIn->leftChild = insertNode(nodeToInsert, nodeToInsertIn->leftChild);
            }

        }
        int leftSubHeight = (nodeToInsertIn->leftChild? nodeToInsertIn-> leftChild->height : -1);
        int rightSubHeight = (nodeToInsertIn->rightChild? nodeToInsertIn->rightChild->height : -1);
        nodeToInsertIn->height = max(leftSubHeight, rightSubHeight) + 1;
        int balanceFactor = leftSubHeight - rightSubHeight;
        
        if(balanceFactor < -1) {
            if(getBalance(nodeToInsertIn->rightChild) > 0) {
                nodeToInsertIn->rightChild = rightRotate(nodeToInsertIn->rightChild);
            }
            return leftRotate(nodeToInsertIn);
        } else if(balanceFactor > 1) {
            if(getBalance(nodeToInsertIn->leftChild) < 0) {
                nodeToInsertIn->leftChild = leftRotate(nodeToInsertIn->leftChild);
            }
            return rightRotate(nodeToInsertIn);
        }

        return nodeToInsertIn;
    }

    void inOrderTraversal(Node *currentNode) {
        if (!currentNode) return;
        inOrderTraversal(currentNode->leftChild);
        cout << "Data: "<< currentNode->data << " Balance: " << getBalance(currentNode) << endl;
        inOrderTraversal(currentNode->rightChild);
    }

public:
    AVLTree(): root(nullptr) {
    }

    void insert(int data) {
        if (!root) {
            root = new Node(data);
            return;
        }
        root = insertNode(new Node(data), root);
    }

    void print() {
        if (!root) {
            cout << "Tree is empty" << endl;
            return;
        }
        inOrderTraversal(root);
        cout << endl;
    }
};

int main() {
    AVLTree tr;
    tr.insert(1);
    tr.insert(2);
    tr.insert(3);
    tr.insert(4);
    tr.insert(5);
    tr.insert(43);
    tr.insert(32);
    tr.insert(-2);
    tr.insert(12);
    tr.insert(32);
    tr.insert(16);

    tr.print();
}

/*
 Just simulating BTree operations' mechanisms ignoring real implementation details
 */

#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int t; // branching factor (minimum number of children)
    bool isLeaf;
    int n; // number of keys
    int *key; // array to hold keys
    Node **children; // array of pointers of type Node resembling the node's children

    Node(const int t): t(t) {
        isLeaf = true;
        n = 0;

        children = new Node *[2 * t];
        key = new int[2 * t - 1];

        for (int i = 0; i < 2 * t; i++) {
            children[i] = nullptr;
        }
    };

    ~Node() {
        delete[] children;
    }
};

class BTree {
private:
    int t;
    Node *root;

public:
    BTree(int t): t(t) {
        root = nullptr;
    }

    bool Search(int key, Node *currentNode = nullptr) {
        if (!root) {
            cout << "Tree is empty\n";
            return false;
        }

        if (!currentNode) currentNode = root;
        int index = 0;

        while (index < currentNode->n && key > currentNode->key[index]) index++;
        if (index < currentNode->n && currentNode->key[index] == key) return true;
        if (currentNode->isLeaf) return false;

        return Search(key, currentNode->children[index]);
    }

    void Insert(int key, Node *currentNode = nullptr) {
        if (!root) {
            root = new Node(this->t);
        }

        if (!currentNode) currentNode = root;
        int index = 0;

        // The logic of the program suggets that we don't wait for an overflow to happen but consistently check
        // through the path we taking from the root to the leaf node (where we will insert the new key) if the current node in the path
        // is full, and if it is we split it and call the search function on the appropriate child pointer, whether it's the original child pointer which now points
        // to the left child or the new right child pointer depedning whether the promoted median is greater than the key to be inserter or not
        // In case the root is full, we simply split it and set the currentNode to the new root starting the insertion logic from there.
        if (currentNode == root && currentNode->n == 2 * t - 1) {
            SplitChild(currentNode, -1);
            currentNode = root;
        }
        while (index < currentNode->n && key > currentNode->key[index]) index++;

        if (currentNode->isLeaf) {
            // Insert the key into the index location after shifting the keys following it one position forward
            // modify the node's number of keys attribitute
            currentNode->n++;
            for (int i = currentNode->n - 1; i >= index; i--) {
                currentNode->key[i] = currentNode->key[i - 1];
            }
            currentNode->key[index] = key;
            return;
        }
        if (currentNode->children[index]->n == 2 * t - 1) {
            SplitChild(currentNode, index);
            if (key > currentNode->key[index]) {
                index++;
            }
        }
        Insert(key, currentNode->children[index]);
    }

    void SplitChild(Node *node, int index) {
        // assumes node's indexd child has 2 * t - 1 keys
        // splits that child node into two nodes each having t - 1 keys and promotes the median key to the parent
        // and finally adjusts the nodes' pointers and sizes as should

        // The spcial case where the node to split is the root can be indicated by having the index equal to -1
        if (index == -1) {
            Node *newRoot = new Node(t);
            newRoot->n++;
            newRoot->isLeaf = false;
            newRoot->key[0] = root->key[t - 1];
            newRoot->children[0] = root;

            // Reusing the SplitChild algorithm instead of re-writing a special case code
            // by making a newRoot node, make it point to the old root node as its first left child
            // then calling the SplitChild on the newRoot
            // since the promoted median is already inserted into the newRoot, the newRoot will have 2 duplicate median keys
            // A simple fix is decrementing the newRoot number of keys to reset the boundaries of that node and ignoring the new median as if it doesn't even exist
            SplitChild(newRoot, 0);
            newRoot->n--;
            root = newRoot;
            return;
        }
        Node *child = node->children[index];

        // create the new child
        Node *newChild = new Node(this->t);

        newChild->isLeaf = child->isLeaf;

        // setting the number of keys to t - 1
        newChild->n = t - 1;

        // setting the number of keys of the original child to t - 1 which is equivalent to keeping the first
        // t - 1 keys and removing the keys after
        child->n = t - 1;

        // declaring a variable to hold the median key index
        int medianIndex = t - 1;

        // declaring a variable to hold the median key value
        int keyToPromote = child->key[medianIndex];

        // copying the t - 1 keys following the median key from the original child to the new child
        for (int i = 0; i < newChild->n; i++) {
            newChild->key[i] = child->key[medianIndex + 1 + i];
        }

        // copying the original child children following the median key into the new child
        if (!child->isLeaf) {
            for (int i = 0; i < newChild->n + 1; i++) {
                newChild->children[i] = child->children[medianIndex + 1 + i];
            }
        }

        // incrementing the parent's number of keys as we are promoting the median key to the parent
        node->n++;

        // making place for the median key by shifting the keys having value greater than it so to put the median key in the right place
        for (int i = node->n - 1; i > index; i--) {
            node->key[i] = node->key[i - 1];
        }

        // inserting the median key into the parent
        node->key[index] = keyToPromote;

        // adjusting the parent's node children pointers
        for (int i = node->n; i > index + 1; i--) {
            node->children[i] = node->children[i - 1];
        }
        node->children[index + 1] = newChild;
    }

    void Delete(int key, Node *node = nullptr) {
        if (!root) {
            cout << "Tree is empty\n";
            return;
        }

        if (!node) node = root;

        int i = 0;
        while (i < node->n && key > node->key[i]) i++;
        if (i == node->n || node->key[i] != key) {
            if (node->isLeaf) {
                cout << "Key doesn't exist\n";
                return;
            }

            Delete(key, node->children[i]);
        } else {
            // key has been found
            if (!node->isLeaf) {
                Node *leftChild = node->children[i];
                int predecessorIndex = leftChild->n - 1;
                swap(leftChild->key[predecessorIndex], node->key[i]);
                Delete(key, leftChild);

            } else {
                for (int j = i; j + 1 < node->n; j++) {
                    node->key[j] = node->key[j + 1];
                }
                node->n--;
            }
        }
        // after deletion occurs, we check for every node if its child number of keys isn't below the minimum
        // and if it is we fix it
        if(node->isLeaf) {
            return;
        }
        if(node->children[i]->n < t - 1) {
            deleteFixUp(i, node);
        }
    }
    // handle the case where the root becomes empty
    void deleteFixUp(int childIndex, Node* parent) {

        Node* child = parent->children[childIndex];
        Node* rightSibling = nullptr;
        Node* leftSibling = nullptr;

        int rightSiblingIndex = childIndex + 1;
        int leftSiblingIndex = childIndex - 1;

        if(rightSiblingIndex <= parent->n) rightSibling = parent->children[rightSiblingIndex];
        if(leftSiblingIndex >= 0) leftSibling = parent->children[leftSiblingIndex];

        // Borrowing from the left sibling
        if(leftSibling && leftSibling->n > t - 1) {

            child->n++;
            for(int i = child->n - 1; i > 0; i--) {
                child->key[i] = child->key[i - 1];
            }
            child->key[0] = parent->key[childIndex - 1];

            for(int i = child->n; i > 0; i--) {
                child->children[i] = child->children[i - 1];
            }
            child->children[0] = leftSibling->children[leftSibling->n];

            parent->key[childIndex - 1] = leftSibling->key[leftSibling->n - 1];
            leftSibling->n--;
            return;
        }

        // Borrowing from the right sibling
        if(rightSibling && rightSibling->n > t - 1) {
            child->n++;
            child->key[child->n - 1] = parent->key[childIndex];

            child->children[child->n] = rightSibling->children[0];

            parent->key[childIndex] = rightSibling->key[0];

            for(int i = 0; i + 1 < rightSibling->n; i++) {
                rightSibling->key[i] = rightSibling->key[i + 1];
            }
            for(int i = 0; i < rightSibling->n; i++) {
                rightSibling->children[i] = rightSibling->children[i + 1];
            }

            rightSibling->n--;
            return;
        }

        // Merging with the right sibling
        if(rightSibling) {
            child->n++;
            child->key[child->n - 1] = parent->key[childIndex];
            for(int i = 0; i < rightSibling->n; i ++) {
                child->key[child->n + i] = rightSibling->key[i];
            }

            for(int i = 0; i <= rightSibling->n; i ++) {
                child->children[child->n + i] = rightSibling->children[i];
            }

            child->n += rightSibling->n;
            delete rightSibling;

            for(int i = childIndex - 1; i + 1< parent->n; i ++) {
                parent->key[i] = parent->key[i + 1];
            }
            for(int i = rightSiblingIndex; i< parent->n; i ++) {
                parent->children[i] = parent->children[i + 1];
            }
            parent->n--;
            if(parent->n == 0) {
                root = child;
            }
        }

        // Merging with the left sibling
        if(leftSibling) {
            Node* newChild = new Node(this->t);
            newChild->isLeaf = child->isLeaf;
            for(int i = 0; i < leftSibling->n; i++) {
                newChild->key[i] = leftSibling->key[i];
            }
            for(int i = 0; i <= leftSibling->n; i++) {
                newChild->children[i] = leftSibling->children[i];
            }
            newChild->n = leftSibling->n;
            newChild->key[newChild->n] = parent->key[childIndex - 1];
            newChild->n++;

            for(int i = 0; i < child->n; i++) {
                newChild->key[newChild->n + i] = child->key[i];
            }
            for(int i = 0; i <= child->n; i++) {
                newChild->children[newChild->n + i] = child->children[i];
            }
            newChild->n += child->n;
            parent->children[childIndex] = newChild;

            for(int i = childIndex - 1; i + 1 < parent->n; i++) {
                parent->key[i] = parent->key[i + 1];
            }

            for(int i = childIndex - 1; i < parent->n; i++) {
                parent->children[i] = parent->children[i + 1];
            }

            parent->n--;
            if(parent->n == 0) {
                root = child;
            }
        }

    }

    // AI generated print function
    void PrintTree() {
        if (!root) {
            cout << "Tree is empty.\n";
            return;
        }

        // Queue holds pairs of (Node pointer, current depth/level)
        queue<pair<Node *, int> > q;
        q.push({root, 0});

        int currentLevel = 0;
        cout << "--- B-Tree Structure (t = " << t << ") ---\nLevel 0: ";

        while (!q.empty()) {
            Node *curr = q.front().first;
            int level = q.front().second;
            q.pop();

            // If we've moved to a new level, print a newline spacer
            if (level > currentLevel) {
                currentLevel = level;
                cout << "\nLevel " << currentLevel << ": ";
            }

            // Print all keys inside the current node bounded by brackets
            cout << "[";
            for (int i = 0; i < curr->n; i++) {
                cout << curr->key[i];
                if (i < curr->n - 1) cout << ",";
            }
            cout << "] ";

            // If this isn't a leaf, push all valid child pointers to the queue
            if (!curr->isLeaf) {
                for (int i = 0; i <= curr->n; i++) {
                    if (curr->children[i] != nullptr) {
                        q.push({curr->children[i], level + 1});
                    }
                }
            }
        }
        cout << "\n-------------------------------------\n";
    }
};

int main() {
    BTree tree(3);
    int input;
    char op;
    while (true) {
        cout << "1. Insert\n2. Delete\nEnter option: ";
        cin >> op;
        cout << "Enter input: ";
        if(op == '1') {
            cin >> input;
            tree.Insert(input);

        } else {
            cin >> input;
            tree.Delete(input);
        }
        tree.PrintTree();
    }
    return 0;
}


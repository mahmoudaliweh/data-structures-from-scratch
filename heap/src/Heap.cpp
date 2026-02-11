#include <iostream>
using namespace std;

class Heap {
private:
    int *heapArray;
    int capacity;
    int size;

    int parent(int index) {
        return (index - 1) / 2;
    }

    int leftChild(int index) {
        return index * 2 + 1;
    }

    int rightChild(int index) {
        return index * 2 + 2;
    }

    void swap(int index1, int index2) {
        int temp = heapArray[index1];
        heapArray[index1] = heapArray[index2];
        heapArray[index2] = temp;
    }

public:
    Heap(int cap = 15): capacity(cap), size(0), heapArray(new int[capacity]) {
    };

    ~Heap() {
        delete[] heapArray;
    }


    void heapifyUp(int index) {
        while (index != 0 && heapArray[parent(index)] < heapArray[index]) {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int left = leftChild(index);
            int right = rightChild(index);
            int largest = index;

            if (left < size && heapArray[left] > heapArray[largest]) {
                largest = left;
            }
            if (right < size && heapArray[right] > heapArray[largest]) {
                largest = right;
            }
            if (largest == index) break;
            swap(largest, index);
            index = largest;
        }
    }

    void insert(int key) {
        if (size == capacity) {
            cout << "Heap is full" << endl;
            return;
        }
        size++;
        heapArray[size - 1] = key;
        heapifyUp(size - 1);
    }

    void remove() {
        if (size == 0) {
            cout << "Heap is empty" << endl;
            return;
        }
        swap(0, size - 1);
        size--;
        heapifyDown(0);
    }

    int peek() {
        if(size == 0) {
            cout << "Heap is empty" << endl;
            return -1;
        }
        return heapArray[0];
    }
};

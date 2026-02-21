#include <iostream>
using namespace std;

class SegmentTree {
private:
    int *tree;
    int size;

    bool isPowerOfTwo(int n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    }

    int getIntervalSum(int query_left, int query_right, int node_left, int node_right, int node = 1) {
        if (query_left <= node_left && node_right <= query_right) {
            return tree[node];
        }
        if (query_right < node_left || node_right < query_left) {
            return 0;
        }

        int left_last = (node_left + node_right) / 2;
        return getIntervalSum(query_left, query_right, node_left, left_last, node * 2) +
               getIntervalSum(query_left, query_right, left_last + 1, node_right, node * 2 + 1);
    }

    void Update(int query_left, int query_right, int node_left, int node_right, int node, int value) {
        if (node_right == query_right && node_left == query_left && node_left == node_right) {
            tree[node] = value;
            return;
        }
        if (query_right < node_left || node_right < query_left) {
            return;
        }
        int left_last = (node_left + node_right) / 2;
        Update(query_left, query_right, node_left, left_last, node * 2, value);
        Update(query_left, query_right, left_last + 1, node_right, node * 2 + 1, value);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

public:
    ~SegmentTree() {
        delete[] tree;
    }

    SegmentTree(int *arr, int n) {
        int k = n;
        while (!isPowerOfTwo(k)) {
            k++;
        }
        size = k;

        tree = new int[2 * k];
        for (int i = 0; i < k; i++) {
            tree[k + i] = 0;
        }
        for (int i = 0; i < n; i++) {
            tree[k + i] = arr[i];
        }
        for (int i = k - 1; i >= 1; i--) {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }


    int query(int l, int r) {
        return getIntervalSum(l, r, 1, size, 1);
    }

    void update(int left, int right, int value) {
        Update(left, right, 1, size, 1, value);
    }
};


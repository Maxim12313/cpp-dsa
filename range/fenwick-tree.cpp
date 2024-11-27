#include <iostream>
#include <vector>

using namespace std;

// tree is 1 indexed, but operations work 0 indexed
template <typename T> struct FenwickTree {
    vector<T> tree;
    FenwickTree(int n) {
        tree.resize(n + 1);
    }
    FenwickTree(vector<int> &v) {
        tree.resize(size(v) + 1);
        for (int i = 0; i < size(v); i++)
            add(i, v[i]);
    }
    T sum(int k) {
        k++;
        T sum = T(0);
        while (k >= 1) {
            sum += tree[k];
            k -= k & -k;
        }
        return sum;
    }
    // [l, r]
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int k, T x) {
        k++;
        while (k < tree.size()) {
            tree[k] += x;
            k += k & -k;
        }
    }
};

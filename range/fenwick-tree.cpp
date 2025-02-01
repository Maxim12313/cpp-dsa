#include <iostream>
#include <vector>

using namespace std;

template <typename T> struct FenwickTree {
    vector<T> tree;

    FenwickTree() {}
    FenwickTree(int n) {
        tree.resize(n);
    }
    FenwickTree(vector<T> &v) {
        init(v);
    }
    // O(n)
    void init(vector<T> &v) {
        tree.assign(size(v), T(0));
        for (int i = 0; i < size(v); i++) {
            tree[i] += v[i];
            int next = i | (i + 1);
            if (next < size(v))
                tree[next] += tree[i];
        }
    }
    // if k < 0, ret 0 still
    T sum(int k) {
        T sum = T(0);
        while (k >= 0) {
            sum += tree[k];
            k = (k & (k + 1)) - 1;
        }
        return sum;
    }
    // [l, r]
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    void add(int k, T change) {
        while (k < size(tree)) {
            tree[k] += change;
            k = k | (k + 1);
        }
    }
};

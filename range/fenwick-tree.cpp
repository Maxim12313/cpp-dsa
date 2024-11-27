#include <iostream>
#include <vector>

using namespace std;

template <typename T> struct FenwickTree {
    vector<T> tree;
    FenwickTree(int n) {
        tree.resize(n);
    }
    T sumHelp(int k) {
        T sum = T(0);
        while (k >= 1) {
            sum += tree[k];
            // go to next closest power of 2
            k -= k & -k;
        }
        return sum;
    }
    // [l, r]
    T sum(int l, int r) {
        return sumHelp(r) - sumHelp(l - 1);
    }

    void add(int k, T x) {
        while (k < tree.size()) {
            tree[k] += x;
            k += k & -k;
        }
    }
};

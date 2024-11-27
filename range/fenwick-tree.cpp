#include <iostream>
#include <vector>

using namespace std;

template <typename T> class FenwickTree {
public:
    vector<T> tree;
    FenwickTree(int n) {
        tree.resize(n);
    }
    T getSum(int k) {
        T sum = T(0);
        while (k >= 1) {
            sum += tree[k];
            // go to next closest power of 2
            k -= k & -k;
        }
        return sum;
    }
    T rangeSum(int l, int r) {
        return getSum(r) - getSum(l - 1);
    }

    void update(int k, T x) {
        while (k < tree.size()) {
            tree[k] += x;
            k += k & -k;
        }
    }
};

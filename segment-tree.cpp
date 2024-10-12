#include <iostream>
#include <vector>

using namespace std;

template <typename T> struct SegTree {
    vector<T> tree;
    T init = 0;

    SegTree(vector<T> &nums) {
        tree.resize(4 * nums.size(), 0);
        build(tree);
    }

    T combine(T a, T b) {
        return a + b;
    }

    void build(vector<T> &nums, int l, int r, int k) {
        if (l == r) {
            tree[k] = nums[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(nums, l, m, 2 * k + 1);
        build(nums, m + 1, r, 2 * k + 2);
        tree[k] = combine(tree[2 * k + 1], tree[2 * k + 2]);
    }

    T query(T l, T r, T k, T outerL, T outerR) {
        if (r < outerL || outerR < l)
            return init;

        if (outerL <= l && r <= outerR)
            return tree[k];

        int m = l + (r - l) / 2;
        return combine(query(l, m, 2 * k + 1, outerL, outerR),
                       query(m + 1, r, 2 * k + 2, outerL, outerR));
    }

    void update(T l, T r, T k, int idx, T val) {
        if (l == r) {
            tree[k] = val;
            return;
        }
        int m = l + (r - l) / 2;
        if (idx <= m)
            update(l, m, 2 * k + 1, idx, val);
        else
            update(m + 1, r, 2 * k + 2, idx, val);

        tree[k] = combine(tree[2 * k + 1], tree[2 * k + 2]);
    }
};

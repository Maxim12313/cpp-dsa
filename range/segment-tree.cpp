#include <iostream>
#include <vector>

using namespace std;

template <typename T> class SegmentTree {
public:
    int n;
    vector<T> tree;
    T init = T(0); // initial value

    SegmentTree(vector<T> &nums) : n(size(nums)) {
        tree.resize(4 * n, init);
        build(nums, 0, n - 1, 0);
    }

    T combine(T a, T b) {
        return max(a, b);
    }

    T query(int l, int r) {
        return query(0, n - 1, 0, l, r);
    }

    void update(int idx, T val) {
        update(0, n - 1, 0, idx, val);
    }

private:
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

    T query(int l, int r, int k, int outerL, int outerR) {
        if (r < outerL || outerR < l)
            return init;

        if (outerL <= l && r <= outerR)
            return tree[k];

        int m = l + (r - l) / 2;
        return combine(query(l, m, 2 * k + 1, outerL, outerR),
                       query(m + 1, r, 2 * k + 2, outerL, outerR));
    }

    void update(int l, int r, int k, int idx, T val) {
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

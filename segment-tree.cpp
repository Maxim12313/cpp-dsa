#include <iostream>
#include <vector>

using namespace std;

int merge(int a, int b, vector<int> &data, int mid) {
    if (mid == data.size() - 1)
        return a;

    if (data[mid] != data[mid + 1])
        return a + b;

    return max(a, b);
}

void build(vector<int> &tree, vector<int> &data, int node, int lo, int hi) {
    if (lo == hi) {
        tree[node] = data[lo];
        return;
    }
    int mid = hi + (lo - hi) / 2;
    build(tree, data, 2 * node + 1, lo, mid);
    build(tree, data, 2 * node + 2, mid + 1, hi);
    tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2], data, mid);
}

int query(vector<int> &tree, vector<int> &data, int node, int lo, int hi,
          int outerLo, int outerHi) {
    if (outerHi < lo || hi < outerLo)
        return 0;

    if (outerLo <= lo && hi <= outerHi)
        return tree[node];

    int mid = lo + (hi - lo) / 2;
    int a = query(tree, data, 2 * node + 1, lo, mid, outerLo, outerHi);
    int b = query(tree, data, 2 * node + 2, mid + 1, hi, outerLo, outerHi);
    return merge(a, b, data, mid);
}

void update(vector<int> &tree, vector<int> &data, int node, int lo, int hi,
            int newVal, int idx) {
    if (lo == hi) {
        tree[node] = newVal;
        return;
    }
    int mid = lo + (hi - lo) / 2;

    if (idx <= mid)
        update(tree, data, 2 * node + 1, lo, mid, newVal, idx);
    else
        update(tree, data, 2 * node + 2, mid + 1, hi, newVal, idx);

    tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2], data, mid);
}

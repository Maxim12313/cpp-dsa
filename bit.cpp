#include <vector>

using namespace std;

int getSum(vector<int> &tree, int k) {
    int sum = 0;
    while (k >= 1) {
        sum += tree[k];
        // go to next closest power of 2
        k -= k & -k;
    }
    return sum;
}

int rangeSum(vector<int> &tree, int l, int r) {
    return getSum(tree, r) - getSum(tree, l - 1);
}

void update(vector<int> &tree, int k, int x) {
    while (k < tree.size()) {
        tree[k] += x;
        k += k & -k;
    }
}

int main() {
    int n = 100;
}

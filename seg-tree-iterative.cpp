#include <vector>

using namespace std;

int getSum(vector<int> &tree, int l, int r, int n) {
    l += n;
    r += n;
    int sum = 0;
    while (l <= r) {
        if (l % 2 == 1)
            sum += tree[l++];
        if (r % 2 == 0)
            sum += tree[r--];
        l /= 2;
        r /= 2;
    }
    return sum;
}

void add(vector<int> &tree, int k, int x, int n) {
    k += n;
    tree[k] = x;
    for (k /= 2; k >= 1; k /= 2)
        tree[k] = tree[2 * k] + tree[2 * k + 1];
}

int main() {}

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> build(vector<int> &nums) {
    int n = nums.size();
    int k = log2(n);
    vector<vector<int>> table(k + 1, vector<int>(n));

    for (int i = 0; i < n; i++)
        table[0][i] = nums[i];

    for (int power = 1; power <= k; power++) {
        for (int pos = 0; pos + (1 << power) <= n; pos++) {
            int left = table[power - 1][pos];
            int right = table[power - 1][pos + (1 << (power - 1))];
            table[power][pos] = min(left, right);
        }
    }
    return table;
}

int getMin(vector<vector<int>> &table, int l, int r) {
    int nearestPow = log2(r - l + 1);
    int left = table[nearestPow][l];
    int right = table[nearestPow][r - (1 << nearestPow) + 1];
    return min(left, right);
}

int main() {
    cout << "put n m where n=size m=[0, m) element val\n";
    int n, m;
    cin >> n >> m;
    vector<int> nums(n);
    for (int &val : nums)
        val = rand() % m;
    cout << "array: \n";
    for (int val : nums)
        cout << val << " ";
    cout << "\n";

    cout << "proceeed with l r for range [l, r]\n";
    vector<vector<int>> table = build(nums);
    while (true) {
        int l, r;
        cin >> l >> r;
        cout << getMin(table, l, r) << "\n";
    }
}

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int p = 9973;
int m = 1e9 + 7;

vector<int64_t> rollingHash(string &s) {
    int n = s.size();
    vector<int64_t> rhash(n);
    int64_t hash = 0;
    for (int i = 0; i < s.size(); i++) {
        hash = hash * p % m;
        hash = (hash + s[i]) % m;
        rhash[i] = hash;
    }
    return rhash;
}

int64_t getWindow(vector<int64_t> &rhash, vector<int64_t> &pow, int l,
                  int currLen) {
    int64_t lval = l == 0 ? 0 : (rhash[l - 1] * pow[currLen]) % m;
    return (m + rhash[l + currLen - 1] - lval) % m;
}

void solve() {
    string s;
    cin >> s;
    vector<int64_t> rhash = rollingHash(s);
    int n = s.size();
    vector<int64_t> pow(n + 1);
    pow[0] = 1;
    for (int i = 1; i <= n; i++)
        pow[i] = (pow[i - 1] * p) % m;

    vector<int> ans;
    for (int len = 1; len <= n; len++) {
        int i;
        for (i = len; i < n; i += len) {
            int currLen = min(len, n - i);
            int64_t expect = getWindow(rhash, pow, 0, currLen);
            int64_t actual = getWindow(rhash, pow, i, currLen);
            if (expect != actual)
                break;
        }
        if (i >= n)
            ans.push_back(len);
    }
    for (int val : ans)
        cout << val << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}

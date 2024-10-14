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

vector<int> prefixSuffix(string &s) {
    int n = s.size();
    vector<int> pi(n);
    int j = pi[0] = 0;
    int i = 1;
    while (i < n) {
        if (s[j] == s[i]) {
            pi[i] = j + 1;
            j++;
            i++;
        } else if (j == 0) {
            pi[i] = 0;
            i++;
        } else {
            j = pi[j - 1];
        }
    }
    return pi;
}

void solve() {
    string a, b;
    cin >> a >> b;
    if (a.size() < b.size()) {
        cout << 0 << "\n";
        return;
    }
    vector<int> pi = prefixSuffix(b);
    int count = 0;
    int i = 0;
    int j = 0;
    while (i < a.size()) {
        if (a[i] == b[j]) {
            i++;
            j++;
        } else if (j == 0) {
            i++;
        } else {
            j = pi[j - 1];
        }

        if (j == b.size()) {
            count++;
            j = pi[j - 1];
        }
    }

    cout << count << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}

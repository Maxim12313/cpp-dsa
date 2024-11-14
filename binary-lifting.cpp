#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <sys/resource.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int l;
int timer;
vector<int> tin;
vector<int> tout;
vector<vector<int>> up;

void dfs(int curr, int prev, vector<vector<int>> &adjList) {
    tin[curr] = timer++;

    up[curr][0] = prev;
    for (int pow = 1; pow <= l && up[curr][pow - 1] != -1; pow++)
        up[curr][pow] = up[up[curr][pow - 1]][pow - 1];

    for (int next : adjList[curr])
        dfs(next, curr, adjList);

    tout[curr] = timer++;
}

void processAncestor(vector<vector<int>> &adjList, int root) {
    int n = adjList.size();
    timer = 0;
    l = ceil(log2(n));
    tin.resize(n);
    tout.resize(n);
    up.assign(n, vector<int>(l + 1, -1));
    dfs(root, -1, adjList);
}

// true if u ancestor of v
bool isAncestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int getKth(int u, int k) {
    for (int i = 0; i <= l && u != -1; i++)
        if (k & (1 << i))
            u = up[u][i];
    return u;
}

int getLca(int u, int v) {
    if (isAncestor(u, v))
        return u;
    if (isAncestor(v, u))
        return v;

    for (int i = 0; i <= l; i++)
        if (!isAncestor(up[u][i], v))
            u = up[u][i];

    return up[u][0];
}

// concise if just need get Kth
void getKthUsage() {
    int n, q;
    cin >> n >> q;
    int POW = ceil(log2(n));
    vector<vector<int>> up(n + 1, vector<int>(POW + 1, 0));
    for (int i = 2; i <= n; i++)
        cin >> up[i][0];

    // if 0, then goes to garbage 0
    for (int pow = 1; pow <= POW; pow++)
        for (int u = 1; u <= n; u++)
            up[u][pow] = up[up[u][pow - 1]][pow - 1];

    while (q--) {
        int u, k;
        cin >> u >> k;
        for (int pow = POW; pow >= 0 && u != -1; pow--)
            if (k & (1 << pow))
                u = up[u][pow];
        cout << (u ? u : -1) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

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

int POW;
int timer;
vector<int> tin;
vector<int> tout;
vector<vector<int>> up;

bool isAncestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

void dfs(int curr, int prev, vector<vector<int>> &adjList) {
    tin[curr] = timer++;

    up[curr][0] = prev;
    for (int pow = 1; pow <= POW; pow++)
        up[curr][pow] = up[up[curr][pow - 1]][pow - 1];

    for (int next : adjList[curr])
        dfs(next, curr, adjList);

    tout[curr] = timer++;
}

int getLCA(int u, int v) {
    if (isAncestor(u, v))
        return u;
    if (isAncestor(v, u))
        return v;

    for (int pow = POW; pow >= 0; pow--)
        if (!isAncestor(up[u][pow], v))
            u = up[u][pow];

    return up[u][0];
}

// full and above if need LCA
void getLCAUsage() {
    int n, q;
    cin >> n >> q;
    POW = ceil(log2(n));
    vector<vector<int>> adjList(n + 1);
    for (int i = 2; i <= n; i++) {
        int prev;
        cin >> prev;
        adjList[prev].push_back(i);
    }
    tin.resize(n + 1);
    tout.resize(n + 1);
    up.assign(n + 1, vector<int>(POW + 1, 0));
    timer = 0;
    tin[0] = timer++;
    dfs(1, 0, adjList);
    tout[0] = timer++;

    while (q--) {
        int u, v;
        cin >> u >> v;
        int res = getLCA(u, v);
        cout << (res ? res : -1) << "\n";
    }
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

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

class LCAForest {
public:
    int POW;
    int timer;
    vector<int> tin;
    vector<int> tout;
    vector<vector<int>> up;
    LCAForest(vector<vector<int>> &adjList) {
        int n = adjList.size();
        POW = ceil(log2(n));
        tin.resize(n + 1);
        tout.resize(n + 1);
        up.assign(n + 1, vector<int>(POW + 1, 0));
        timer = 0;
        tin[0] = timer++;
        dfs(1, 0, adjList);
        tout[0] = timer++;
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

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
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

    int getKth(int u, int k) {
        for (int pow = POW; pow >= 0 && u != -1; pow--)
            if (k & (1 << pow))
                u = up[u][pow];
        return u ? u : -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

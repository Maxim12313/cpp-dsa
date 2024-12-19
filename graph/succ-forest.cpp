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

class SuccForest {
    vector<vector<int>> succ;
    int POW;

    void dfs(vector<int> &v, int u, vector<bool> &visited) {
        if (visited[u])
            return;
        visited[u] = true;

        succ[u][0] = v[u];
        dfs(v, v[u], visited);

        for (int pow = 1; pow <= POW && u != -1; pow++)
            succ[u][pow] = succ[succ[u][pow - 1]][pow - 1];
    }

    void build(vector<int> &v) {
        int n = int(size(v));
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++)
            dfs(v, i, visited);
    }

public:
    SuccForest(vector<int> &v) {
        int n = int(size(v));
        POW = int(ceil(log2(n)));
        succ.assign(n, vector<int>(POW + 1, -1));
        build(v);
    }

    int getKthSucc(int u, int k) {
        for (int pow = POW; pow >= 0 && u != -1; pow--)
            if (k & (1 << pow))
                u = succ[u][pow];
        return u;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i]--;
    }

    SuccForest succ(v);
    while (true) {
        int node, k;
        cin >> node >> k;
        node--;
        int res = succ.getKthSucc(node, k);
        cout << res + 1 << "\n";
    }
}

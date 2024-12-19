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

// acyclic?
void dfsSort(vector<vector<int>> &adjList, int curr, vector<int> &ordering,
             vector<bool> &visited) {
    if (visited[curr])
        return;
    visited[curr] = true;
    for (int next : adjList[curr])
        dfsSort(adjList, next, ordering, visited);
    ordering.push_back(curr);
}

vector<int> topologicalSort(vector<vector<int>> &adjList) {
    int n = size(adjList);
    vector<int> ordering;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++)
        dfsSort(adjList, i, ordering, visited);
    reverse(begin(ordering), end(ordering));
    return ordering;
}

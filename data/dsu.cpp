#include <numeric>
#include <vector>

using namespace std;

class DSU {
public:
    int count;
    vector<int> rep;

    DSU(int n) : count(n) {
        rep.resize(n);
        iota(begin(rep), end(rep), 0);
    }

    int find(int a) {
        if (rep[a] == a)
            return a;
        return rep[a] = find(rep[a]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b)
            count--;
        if (a > b)
            swap(a, b);
        rep[b] = a;
    }
};

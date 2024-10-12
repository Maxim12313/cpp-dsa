#include <iostream>
#include <vector>

using namespace std;

vector<int64_t> rollingHash(string &s, int window) {
    const int p = 9973;
    const int m = 1e9 + 7;

    int64_t hash = 0;
    for (int i = 0; i < window; i++)
        hash = ((hash * p) % m + s[i]) % m;

    int64_t big = 1;
    for (int i = 1; i < window; i++)
        big = (big * p) % m;

    vector<int64_t> rolling(s.size() - window + 1);
    rolling[0] = hash;
    for (int i = window; i < s.size(); i++) {
        int64_t remove = s[i - window] * big % m;
        hash = ((m + hash - remove) % m * p % m + s[i]) % m;
        rolling[i - window + 1] = hash;
    }
    return rolling;
}

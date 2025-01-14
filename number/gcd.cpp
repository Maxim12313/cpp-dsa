#include <cstdint>
#include <iostream>

using namespace std;

struct Item {
    int64_t g, a, b;
    Item(int64_t g, int64_t a, int64_t b) : g(g), a(a), b(b) {}
};

int64_t gcd(int64_t a, int64_t b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

Item gcd_extended(int64_t x, int64_t y) {
    if (y == 0)
        return Item(x, 1, 0);

    int64_t q = x / y;
    auto [g, a, b] = gcd_extended(y, x % y);
    int64_t newA = b;
    int64_t newB = a - b * q;
    return Item(g, newA, newB);
}
int main() {
    while (true) {
        int64_t x, y;
        cin >> x >> y;
        auto [g, a, b] = gcd_extended(x, y);
        cout << g << " " << a << " " << b << "\n";
    }
}

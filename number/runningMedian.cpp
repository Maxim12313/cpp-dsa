#include <set>
#include <vector>

using namespace std;

template <typename T> class RunMedian {
public:
    multiset<T, greater<T>> low; // non increasing
    multiset<T> high;            // non decreasing

    int size() {
        return low.size() + high.size();
    }

    // assuming choose lower for even median
    T median() {
        assert(size() > 0);
        if (low.size() >= high.size())
            return *begin(low);
        return *begin(high);
    }

    // low has extra if odd
    void push(T val) {
        val = balance(val);
        if (low.size() <= high.size())
            low.insert(val);
        else
            high.insert(val);
    }

    void erase(T val) {
        auto it1 = low.find(val);
        auto it2 = high.find(val);
        assert(it1 != end(low) || it2 != end(high));
        if (it1 != end(low))
            low.erase(it1);
        else
            high.erase(it2);
        rebalance();
    }

private:
    // balance and return the value between lo and hi to insert
    T balance(T val) {
        if (!low.empty() && val < *begin(low)) {
            auto it = begin(low);
            T temp = *it;
            low.erase(it);
            low.insert(val);
            return temp;
        }
        if (!high.empty() && val > *begin(high)) {
            auto it = begin(high);
            T temp = *it;
            high.erase(it);
            high.insert(val);
            return temp;
        }
        return val;
    }

    // rebalance after erase
    void rebalance() {
        if (size(low) < size(high)) {
            auto it = begin(high);
            low.insert(*it);
            high.erase(it);
        } else if (size(low) > size(high) + 1) {
            auto it = begin(low);
            high.insert(*it);
            low.erase(it);
        }
    }
};

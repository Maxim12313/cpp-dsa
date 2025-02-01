#include <iostream>

using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}

    double dist(Point &o) {
        return sqrt(abs(pow(x, 2) - pow(o.x, 2))) +
               sqrt(abs(pow(y, 2) - pow(o.y, 2)));
    }
};

pair<Point, Point> helpPoint(vector<Point> &pointsX, vector<Point> &pointsY,
                             int l, int r) {
    if (l == r)
        return {Point(INT_MIN, INT_MIN), Point(INT_MAX, INT_MAX)};

    int m = l + (r - l) / 2;
    pair<Point, Point> a = helpPoint(pointsX, pointsY, l, m);
    pair<Point, Point> b = helpPoint(pointsX, pointsY, m + 1, r);
    double d = min(a.first.dist(a.second), b.first.dist(b.second));
    vector<Point> filter;
    for ()
}

pair<Point, Point> closestPoint(vector<Point> &points) {
    sort(begin(points), end(points),
         [](Point &a, Point &b) { return a.x < b.x; });

    vector<Point> pointsY = points;
    sort(begin(pointsY), end(pointsY),
         [](Point &a, Point &b) { return a.y < b.y; });
    pair<Point, Point> ans = helpPoint(points, pointsY, 0, size(points) - 1);
}

int main() {}

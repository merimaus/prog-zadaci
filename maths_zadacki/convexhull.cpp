#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct Point {
    int x;
    int y;
    
    Point() {
        x = 0;
        y = 0;
    }
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    bool operator==(const Point& p) {
        return x == p.x && y == p.y;
    }
};

bool compare(const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int is_right(Point& a, Point& b, Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Point> convex_hull(vector<Point>& points) {
    int n = points.size();
    
    vector<pair<Point, Point>> E;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            
            bool valid = true;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                if (is_right(points[i], points[j], points[k]) > 0) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                E.emplace_back(points[i], points[j]);
            }
        }
    }
    
    vector<Point> res;
    for (int i = 0; i < E.size(); i++) {
        const Point &p = E[i].first;
        if (find(res.begin(), res.end(), p) == res.end()) {
            res.push_back(p);
        }
    }
    sort(res.begin(), res.end(), compare);
    return res;
}

int main(int argc, char *argv[]) {
    vector<Point> points = {{1, 1}, {-12, -3}, {2, 2}, {-2, -6}, {2, 4}, {3, 3}, {4, 2}, {3, 0}};
    
    vector<Point> hull = convex_hull(points);
    for (int i = 0; i < hull.size(); i++) {
        cout << "(" << hull[i].x << ", " << hull[i].y << ")" << endl;
    }
    
    return 0;
}
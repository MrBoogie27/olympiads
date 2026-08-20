#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    long long cross(const Point& O, const Point& A, const Point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
};

vector<Point> convexHull(vector<Point> points) {
    int n = points.size();
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    
    vector<Point> hull;
    
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && 
               hull[hull.size()-2].cross(hull[hull.size()-1], points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower_size && 
               hull[hull.size()-2].cross(hull[hull.size()-1], points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    
    hull.pop_back();
    return hull;
}

int main() {
    vector<Point> points = {{0,0}, {1,1}, {2,2}, {0,2}, {2,0}};
    vector<Point> hull = convexHull(points);
    
    cout << "Convex Hull:\n";
    for (auto p : hull) cout << "(" << p.x << "," << p.y << ")\n";
    
    return 0;
}

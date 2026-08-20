#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


struct Point2D {
  ll x, y;
  
  bool operator<(const Point2D& other) const {
    return tie(x, y) < tie(other.x, other.y);
  }
  
  bool operator==(const Point2D& other) const {
    return tie(x, y) == tie(other.x, other.y);
  }
  
  bool operator!=(const Point2D& other) const {
    return !(*this == other);
  }
  
  bool operator<=(const Point2D& other) const {
    return *this < other || *this == other;
  }
  
  bool operator>(const Point2D& other) const {
    return other < *this;
  }
  
  bool operator>=(const Point2D& other) const {
    return other <= *this;
  }
  
  // Арифметика
  Point2D operator+(const Point2D& p) const {
    return {x + p.x, y + p.y};
  }
  
  Point2D operator-(const Point2D& p) const {
    return {x - p.x, y - p.y};
  }
  
  Point2D operator*(ll t) const {
    return {x * t, y * t};
  }
  
  Point2D& operator+=(const Point2D& p) {
    x += p.x;
    y += p.y;
    return *this;
  }
  
  Point2D& operator-=(const Point2D& p) {
    x -= p.x;
    y -= p.y;
    return *this;
  }
  
  Point2D& operator*=(ll t) {
    x *= t;
    y *= t;
    return *this;
  }

  // Скалярное произведение (dot product)
  ll dot(const Point2D& v) const {
    return x * v.x + y * v.y;
  }

  // Векторное произведение (cross product) - в 2D возвращает скаляр
  ll cross(const Point2D& v) const {
    return x * v.y - y * v.x;
  }

  // Квадрат длины вектора (для целых чисел)
  ll length() const {
    return x * x + y * y;
  }
};

inline ll squaredDistance(const Point2D& p1, const Point2D& p2) {
  ll dx = p1.x - p2.x;
  ll dy = p1.y - p2.y;
  return dx * dx + dy * dy;
}

// Евклидово расстояние
inline double euclideanDistance(const Point2D& p1, const Point2D& p2) {
  return sqrt(squaredDistance(p1, p2));
}

// Манхеттанское расстояние
inline ll manhattanDistance(const Point2D& p1, const Point2D& p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

// Расстояние Чебышева
inline ll chebyshevDistance(const Point2D& p1, const Point2D& p2) {
  return max(abs(p1.x - p2.x), abs(p1.y - p2.y));
}

struct Line {
  Point2D p;       // Точка на линии
  Point2D dir;     // Направляющий вектор

  // Параметрическое уравнение: point(t) = p + dir*t
  Point2D pointAt(ll t) const {
    return {p.x + dir.x * t, p.y + dir.y * t};
  }
};

struct Segment {
  Point2D a, b;
  
  // Квадрат длины отрезка (целочисленная)
  ll squaredLength() const {
    ll dx = b.x - a.x;
    ll dy = b.y - a.y;
    return dx * dx + dy * dy;
  }
  
  // Проверка: лежит ли точка на отрезке?
  bool containsPoint(const Point2D& p) const {
    Point2D ab{b.x - a.x, b.y - a.y};
    Point2D ap{p.x - a.x, p.y - a.y};
    
    // Коллинеарность (кросс-произведение = 0)
    if (ab.cross(ap) != 0) return false;
    
    // Проверка границ [a, b]
    return ap.dot(ab) >= 0 && ap.dot(ab) <= ab.length();
  }
};

struct Circle {
  Point2D center;
  ll radius;  // целочисленный радиус
  
  // Проверка: лежит ли точка внутри окружности?
  bool containsPoint(const Point2D& p) const {
    ll dist_sq = squaredDistance(center, p);
    return dist_sq <= radius * radius;
  }
  
  // Проверка: лежит ли точка на окружности?
  bool onCircle(const Point2D& p) const {
    ll dist_sq = squaredDistance(center, p);
    return dist_sq == radius * radius;
  }
  
  // Пересечение двух окружностей
  // Возвращает: -1 = совпадают, 0 = нет пересечений, 
  //             1 = касание (1 точка), 2 = пересечение (2 точки)
  // Точки пересечения заполняются в вектор points
  int intersectsWith(const Circle& other, vector<Point2D>& points) const {
    ll d_sq = squaredDistance(center, other.center);
    double d = sqrt(static_cast<double>(d_sq));
    ll r1 = radius;
    ll r2 = other.radius;
    
    const double EPS = 1e-9;
    
    // Совпадают
    if (d_sq == 0 && r1 == r2) return -1;
    
    // Не пересекаются (далеко)
    if (d > r1 + r2 + EPS) return 0;
    
    // Не пересекаются (одна внутри другой)
    if (d < abs(r1 - r2) - EPS) return 0;
    
    // Касание внешнее
    if (abs(d - (r1 + r2)) < EPS) return 1;
    
    // Касание внутреннее
    if (abs(d - abs(r1 - r2)) < EPS) return 1;
    
    // Полное пересечение (2 точки)
    // Используем формулы для целых координат
    double a = (r1 * r1 - r2 * r2 + d * d) / (2.0 * d);
    double h_sq = r1 * r1 - a * a;
    
    if (h_sq < 0) return 0;
    
    double h = sqrt(h_sq);
    double px = center.x + a * (other.center.x - center.x) / d;
    double py = center.y + a * (other.center.y - center.y) / d;
    
    points.push_back({
      static_cast<ll>(round(px + h * (other.center.y - center.y) / d)),
      static_cast<ll>(round(py - h * (other.center.x - center.x) / d))
    });
    
    points.push_back({
      static_cast<ll>(round(px - h * (other.center.y - center.y) / d)),
      static_cast<ll>(round(py + h * (other.center.x - center.x) / d))
    });
    
    return 2;
  }
};

#include "../geometry.h"

using namespace std;

void test_point2d_comparison() {
  cout << "Testing Point2D comparison...\n";
  
  Point2D p1 = {1, 2};
  Point2D p2 = {1, 2};
  Point2D p3 = {2, 1};
  Point2D p4 = {1, 3};
  
  assert(p1 == p2);
  assert(!(p1 == p3));
  assert((p1 < p3));  // (1,2) < (2,1)
  assert((p3 > p1));  // (2,1) > (1,2)
  assert((p1 < p4));  // (1,2) < (1,3)
  
  cout << "✓ Point2D comparison PASSED\n";
}

void test_point2d_arithmetic() {
  cout << "Testing Point2D arithmetic...\n";
  
  Point2D p1 = {1, 2};
  Point2D p2 = {3, 4};
  
  Point2D sum = p1 + p2;
  assert(sum.x == 4 && sum.y == 6);
  
  Point2D diff = p2 - p1;
  assert(diff.x == 2 && diff.y == 2);
  
  Point2D scaled = p1 * 3;
  assert(scaled.x == 3 && scaled.y == 6);
  
  cout << "✓ Point2D arithmetic PASSED\n";
}

void test_vector2d_dot_cross() {
  cout << "Testing Vector2D dot and cross products...\n";
  
  Point2D v1{3, 4};
  Point2D v2{1, 2};
  
  // Dot product: 3*1 + 4*2 = 11
  assert(v1.dot(v2) == 11);
  
  // Cross product (в 2D): 3*2 - 4*1 = 2
  assert(v1.cross(v2) == 2);
  
  // Перпендикулярные векторы
  Point2D v3{1, 0};
  Point2D v4{0, 1};
  assert(v3.dot(v4) == 0);
  
  // Anti-commutative свойство cross product
  assert(v1.cross(v2) == -v2.cross(v1));
  
  cout << "✓ Vector2D dot and cross PASSED\n";
}

void test_vector2d_length() {
  cout << "Testing Vector2D length...\n";
  
  Point2D v1{3, 4};
  assert(v1.length() == 25);  // 3^2 + 4^2 = 25
  
  Point2D v2{0, 0};
  assert(v2.length() == 0);
  
  Point2D v3{1, 1};
  assert(v3.length() == 2);
  
  cout << "✓ Vector2D length PASSED\n";
}

void test_euclidean_distance() {
  cout << "Testing euclidean distance...\n";
  
  Point2D p1 = {0, 0};
  Point2D p2 = {3, 4};
  
  double dist = euclideanDistance(p1, p2);
  assert(abs(dist - 5.0) < 1e-9);  // 3-4-5 треугольник
  
  Point2D p3 = {1, 1};
  Point2D p4 = {4, 5};
  dist = euclideanDistance(p3, p4);
  assert(abs(dist - 5.0) < 1e-9);  // расстояние = sqrt(9+16) = 5
  
  // Одинаковые точки
  Point2D p5 = {2, 3};
  assert(euclideanDistance(p5, p5) < 1e-9);
  
  cout << "✓ euclidean distance PASSED\n";
}

void test_squared_distance() {
  cout << "Testing squared distance...\n";
  
  Point2D p1 = {0, 0};
  Point2D p2 = {3, 4};
  assert(squaredDistance(p1, p2) == 25);  // 9 + 16 = 25
  
  Point2D p3 = {1, 2};
  Point2D p4 = {4, 6};
  assert(squaredDistance(p3, p4) == 25);  // 9 + 16 = 25
  
  cout << "✓ squared distance PASSED\n";
}

void test_manhattan_distance() {
  cout << "Testing Manhattan distance...\n";
  
  Point2D p1 = {0, 0};
  Point2D p2 = {3, 4};
  assert(manhattanDistance(p1, p2) == 7);  // |3| + |4| = 7
  
  Point2D p3 = {-2, 3};
  Point2D p4 = {1, -1};
  assert(manhattanDistance(p3, p4) == 7);  // |3| + |4| = 7
  
  cout << "✓ Manhattan distance PASSED\n";
}

void test_chebyshev_distance() {
  cout << "Testing Chebyshev distance...\n";
  
  Point2D p1 = {0, 0};
  Point2D p2 = {3, 4};
  assert(chebyshevDistance(p1, p2) == 4);  // max(3, 4) = 4
  
  Point2D p3 = {1, 1};
  Point2D p4 = {5, 3};
  assert(chebyshevDistance(p3, p4) == 4);  // max(4, 2) = 4
  
  cout << "✓ Chebyshev distance PASSED\n";
}

void test_segment_contains_point() {
  cout << "Testing Segment containsPoint...\n";
  
  Segment seg = {{0, 0}, {4, 4}};
  
  assert(seg.containsPoint({0, 0}));  // начало
  assert(seg.containsPoint({4, 4}));  // конец
  assert(seg.containsPoint({2, 2}));  // середина
  assert(!seg.containsPoint({1, 2}));  // не на линии
  assert(!seg.containsPoint({5, 5}));  // на линии, но вне отрезка
  
  // Горизонтальный отрезок
  Segment seg2 = {{0, 0}, {5, 0}};
  assert(seg2.containsPoint({2, 0}));
  assert(!seg2.containsPoint({2, 1}));
  assert(!seg2.containsPoint({6, 0}));
  
  cout << "✓ Segment containsPoint PASSED\n";
}

void test_circle_contains_point() {
  cout << "Testing Circle containsPoint...\n";
  
  Circle circle = {{0, 0}, 5};
  
  assert(circle.containsPoint({0, 0}));  // центр
  assert(circle.containsPoint({3, 4}));  // на границе (3-4-5 треугольник)
  assert(circle.containsPoint({2, 2}));  // внутри
  assert(!circle.containsPoint({4, 4}));  // вне круга
  
  cout << "✓ Circle containsPoint PASSED\n";
}

void test_circle_on_circle() {
  cout << "Testing Circle onCircle...\n";
  
  Circle circle = {{0, 0}, 5};
  
  assert(circle.onCircle({3, 4}));   // на окружности
  assert(circle.onCircle({5, 0}));   // на окружности
  assert(!circle.onCircle({2, 2}));  // внутри
  assert(!circle.onCircle({6, 0}));  // вне
  
  cout << "✓ Circle onCircle PASSED\n";
}

void test_circle_intersects() {
  cout << "Testing Circle intersectsWith...\n";
  
  // Тест 1: Касание внешнее (r1 + r2 = d)
  Circle c1 = {{0, 0}, 3};
  Circle c2 = {{5, 0}, 2};  // расстояние = 5 = 3 + 2
  
  vector<Point2D> points;
  int result = c1.intersectsWith(c2, points);
  assert(result == 1);  // касание
  points.clear();
  
  // Тест 2: Не пересекаются (далеко)
  Circle c3 = {{0, 0}, 2};
  Circle c4 = {{10, 0}, 2};  // расстояние = 10 > 2+2=4
  points.clear();
  result = c3.intersectsWith(c4, points);
  assert(result == 0);
  points.clear();
  
  // Тест 3: Пересечение (2 точки)
  Circle c5 = {{0, 0}, 5};
  Circle c6 = {{3, 0}, 4};  // расстояние = 3, |5-4| < 3 < 5+4
  points.clear();
  result = c5.intersectsWith(c6, points);
  assert(result == 2);  // две точки пересечения
  assert(points.size() == 2);
  points.clear();
  
  // Тест 4: Совпадают
  Circle c7 = {{0, 0}, 5};
  Circle c8 = {{0, 0}, 5};
  points.clear();
  result = c7.intersectsWith(c8, points);
  assert(result == -1);  // совпадают
  
  cout << "✓ Circle intersectsWith PASSED\n";
}

int main() {
  cout << "\n=== GEOMETRY TESTS ===\n\n";
  
  test_point2d_comparison();
  test_point2d_arithmetic();
  test_vector2d_dot_cross();
  test_vector2d_length();
  test_euclidean_distance();
  test_squared_distance();
  test_manhattan_distance();
  test_chebyshev_distance();
  test_segment_contains_point();
  test_circle_contains_point();
  test_circle_on_circle();
  test_circle_intersects();
  
  cout << "\n✓✓✓ ALL GEOMETRY TESTS PASSED ✓✓✓\n\n";
  return 0;
}

#include "../combinatorics.h"
#include <cassert>
#include <iostream>

using namespace std;

void test_binomial() {
  cout << "Testing binomial()...\n";

  // C(5, 2) = 10
  assert(binomial_mod(5, 2) == 10);

  // C(10, 3) = 120
  assert(binomial_mod(10, 3) == 120);

  // C(n, 0) = 1
  assert(binomial_mod(5, 0) == 1);

  // C(n, n) = 1
  assert(binomial_mod(5, 5) == 1);

  cout << "✓ binomial PASSED\n";
}

void test_pascals_triangle() {
  cout << "Testing pascals_triangle()...\n";

  // Тест 1: полный треугольник (K = n по умолчанию)
  auto triangle = pascals_triangle(4);

  assert(triangle[0][0] == 1);
  assert(triangle[2][0] == 1);
  assert(triangle[2][1] == 2);
  assert(triangle[2][2] == 1);
  assert(triangle[3][0] == 1);
  assert(triangle[3][1] == 3);
  assert(triangle[3][2] == 3);
  assert(triangle[3][3] == 1);

  // Тест 2: треугольник с ограничением K = 2
  // Нужны только C(i, 0), C(i, 1), C(i, 2)
  auto triangle_limited = pascals_triangle(10, 2);

  assert(triangle_limited.size() == 11);   // 0..10
  assert(triangle_limited[0].size() == 3); // 0..2 (K=2)

  assert(triangle_limited[5][0] == 1);  // C(5,0) = 1
  assert(triangle_limited[5][1] == 5);  // C(5,1) = 5
  assert(triangle_limited[5][2] == 10); // C(5,2) = 10

  assert(triangle_limited[10][0] == 1);  // C(10,0) = 1
  assert(triangle_limited[10][1] == 10); // C(10,1) = 10
  assert(triangle_limited[10][2] == 45); // C(10,2) = 45

  // Тест 3: большой треугольник с ограничением
  auto triangle_100 = pascals_triangle(100, 5);
  assert(triangle_100[100][0] == 1);    // C(100,0) = 1
  assert(triangle_100[100][1] == 100);  // C(100,1) = 100
  assert(triangle_100[100][2] == 4950); // C(100,2) = 4950

  cout << "✓ pascals_triangle PASSED\n";
}

void test_permutation() {
  cout << "Testing permutation()...\n";

  // P(5, 2) = 5 * 4 = 20
  assert(permutation_mod(5, 2) == 20);

  // P(4, 3) = 4 * 3 * 2 = 24
  assert(permutation_mod(4, 3) == 24);

  // P(n, 0) = 1
  assert(permutation_mod(5, 0) == 1);

  cout << "✓ permutation PASSED\n";
}

void test_combinations_with_repetition() {
  cout << "Testing combinations_with_repetition()...\n";

  // H(3, 2) = C(3+2-1, 2) = C(4, 2) = 6
  assert(combinations_with_repetition_mod(3, 2) == 6);

  // H(2, 3) = C(2+3-1, 3) = C(4, 3) = 4
  assert(combinations_with_repetition_mod(2, 3) == 4);

  cout << "✓ combinations_with_repetition PASSED\n";
}

void test_catalan() {
  cout << "Testing catalan()...\n";

  // C(0) = 1
  assert(catalan_mod(0) == 1);

  // C(1) = 1
  assert(catalan_mod(1) == 1);

  // C(2) = 2
  assert(catalan_mod(2) == 2);

  // C(3) = 5
  assert(catalan_mod(3) == 5);

  // C(4) = 14
  assert(catalan_mod(4) == 14);

  cout << "✓ catalan PASSED\n";
}

void test_catalan_dp() {
  cout << "Testing catalan_dp()...\n";

  auto cat = catalan_dp(5);

  assert(cat[0] == 1);
  assert(cat[1] == 1);
  assert(cat[2] == 2);
  assert(cat[3] == 5);
  assert(cat[4] == 14);
  assert(cat[5] == 42);

  cout << "✓ catalan_dp PASSED\n";
}

void test_bell_numbers() {
  cout << "Testing bell_numbers()...\n";

  auto bell = bell_numbers(5);

  assert(bell[0] == 1);  // B(0) = 1
  assert(bell[1] == 1);  // B(1) = 1
  assert(bell[2] == 2);  // B(2) = 2
  assert(bell[3] == 5);  // B(3) = 5
  assert(bell[4] == 15); // B(4) = 15
  assert(bell[5] == 52); // B(5) = 52

  cout << "✓ bell_numbers PASSED\n";
}

void test_stirling_second() {
  cout << "Testing stirling_second()...\n";

  vector<vector<ll>> stirlings_second = stirling_second(5);

  // S(3, 2) = 3 (разбиения {1}{2,3}, {2}{1,3}, {3}{1,2})
  assert(stirlings_second[3][2] == 3);

  // S(4, 2) = 7
  assert(stirlings_second[4][2] == 7);

  // S(n, 1) = 1
  assert(stirlings_second[5][1] == 1);

  // S(n, n) = 1
  assert(stirlings_second[5][5] == 1);

  cout << "✓ stirling_second PASSED\n";
}

int main() {
  cout << "\n=== COMBINATORICS TESTS ===\n\n";
  precompute_factorials(1'000);

  test_binomial();
  test_pascals_triangle();
  test_permutation();
  test_combinations_with_repetition();
  test_catalan();
  test_catalan_dp();
  test_bell_numbers();
  test_stirling_second();

  cout << "\n✓✓✓ ALL COMBINATORICS TESTS PASSED ✓✓✓\n\n";
  return 0;
}

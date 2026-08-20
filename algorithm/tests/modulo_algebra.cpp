#include "../modulo_algebra.h"

// ===================== Тесты для multiply =====================

void test_multiply_basic() {
  assert(multiply(0, 0) == 0);
  assert(multiply(0, 5) == 0);
  assert(multiply(5, 0) == 0);
  assert(multiply(1, 1) == 1);
  assert(multiply(2, 3) == 6);
  assert(multiply(10, 10) == 100);
  cout << "test_multiply_basic: PASSED\n";
}

void test_multiply_mod() {
  // (MOD - 1) * (MOD - 1) = (MOD - 1)^2 = MOD^2 - 2*MOD + 1 ≡ 1 (mod MOD)
  assert(multiply(MOD - 1, MOD - 1) == 1);
  // (MOD - 1) * 1 = MOD - 1
  assert(multiply(MOD - 1, 1) == MOD - 1);
  // (MOD - 1) * 2 = 2*MOD - 2 ≡ MOD - 2 (mod MOD)
  assert(multiply(MOD - 1, 2) == MOD - 2);
  // Большое произведение с взятием остатка
  assert(multiply(123456789, 987654321) == (123456789LL * 987654321LL) % MOD);
  cout << "test_multiply_mod: PASSED\n";
}

void test_multiply_large() {
  // Значения больше MOD
  assert(multiply(MOD + 5, MOD + 3) == multiply(5, 3));
  assert(multiply(MOD + 5, MOD + 3) == 15);
  assert(multiply(MOD * 2, MOD * 2) == 0);
  cout << "test_multiply_large: PASSED\n";
}

// ===================== Тесты для binary_pow =====================

void test_binary_pow_zero_one() {
  // Любое число в степени 0 = 1
  assert(binary_pow(0, 0) == 1);
  assert(binary_pow(1, 0) == 1);
  assert(binary_pow(5, 0) == 1);
  assert(binary_pow(MOD - 1, 0) == 1);
  // Число в степени 1 = само число
  assert(binary_pow(0, 1) == 0);
  assert(binary_pow(1, 1) == 1);
  assert(binary_pow(5, 1) == 5);
  assert(binary_pow(MOD - 1, 1) == MOD - 1);
  cout << "test_binary_pow_zero_one: PASSED\n";
}

void test_binary_pow_two() {
  // Степень 2
  assert(binary_pow(2, 2) == 4);
  assert(binary_pow(3, 2) == 9);
  assert(binary_pow(5, 2) == 25);
  assert(binary_pow(MOD - 1, 2) == multiply(MOD - 1, MOD - 1));
  cout << "test_binary_pow_two: PASSED\n";
}

void test_binary_pow_small() {
  // Небольшие степени (3, 4, 5)
  assert(binary_pow(2, 3) == 8);
  assert(binary_pow(2, 4) == 16);
  assert(binary_pow(2, 5) == 32);
  assert(binary_pow(3, 3) == 27);
  assert(binary_pow(10, 3) == 1000);
  cout << "test_binary_pow_small: PASSED\n";
}

void test_binary_pow_large_exp() {
  // По малой теореме Ферма: x^(MOD-1) ≡ 1 (mod MOD) для x не кратного MOD
  assert(binary_pow(2, MOD - 1) == 1);
  assert(binary_pow(3, MOD - 1) == 1);
  assert(binary_pow(12345, MOD - 1) == 1);
  // x^MOD ≡ x (mod MOD)
  assert(binary_pow(2, MOD) == 2);
  assert(binary_pow(5, MOD) == 5);
  assert(binary_pow(MOD - 1, MOD) == MOD - 1);
  cout << "test_binary_pow_large_exp: PASSED\n";
}

void test_binary_pow_mod_properties() {
  // Проверка свойства: x^(a+b) = x^a * x^b
  // x^10 = x^5 * x^5
  ll x = 7;
  ll p1 = binary_pow(x, 5);
  ll p2 = binary_pow(x, 5);
  assert(multiply(p1, p2) == binary_pow(x, 10));
  // Проверка: (x^a)^b = x^(a*b)
  // (x^3)^2 = x^6
  ll p3 = binary_pow(x, 3);
  assert(binary_pow(p3, 2) == binary_pow(x, 6));
  cout << "test_binary_pow_mod_properties: PASSED\n";
}

// ===================== Тесты для devide =====================

void test_devide_basic() {
  assert(devide(0, 1) == 0);
  assert(devide(1, 1) == 1);
  assert(devide(5, 1) == 5);
  assert(devide(MOD - 1, 1) == MOD - 1);
  cout << "test_devide_basic: PASSED\n";
}

void test_devide_by_self() {
  // x / x = 1 (mod MOD) для x ≠ 0
  assert(devide(1, 1) == 1);
  assert(devide(2, 2) == 1);
  assert(devide(5, 5) == 1);
  assert(devide(123456, 123456) == 1);
  assert(devide(MOD - 1, MOD - 1) == 1);
  cout << "test_devide_by_self: PASSED\n";
}

void test_devide_inverse() {
  // Проверка: x / y = x * y^(-1)
  // Умножаем результат деления обратно на y, должны получить x
  for (ll x = 1; x < 20; ++x) {
    for (ll y = 1; y < 20; ++y) {
      ll result = devide(x, y);
      assert(multiply(result, y) == x);
    }
  }
  cout << "test_devide_inverse: PASSED\n";
}

void test_devide_large() {
  // Деление больших чисел
  assert(devide(MOD - 1, 2) == (MOD - 1) / 2);  // (MOD-1)/2 * 2 = MOD - 1
  assert(devide(MOD - 1, MOD - 1) == 1);
  assert(devide(MOD, 1) == 0);  // MOD ≡ 0
  cout << "test_devide_large: PASSED\n";
}

void test_devide_roundtrip() {
  // Проверка через умножение: a == devide(multiply(a, b), b)
  for (ll a = 1; a < 30; ++a) {
    for (ll b = 1; b < 30; ++b) {
      ll prod = multiply(a, b);
      assert(devide(prod, b) == a);
    }
  }
  cout << "test_devide_roundtrip: PASSED\n";
}

int main() {
  cout << "=== Тесты для multiply ===\n";
  test_multiply_basic();
  test_multiply_mod();
  test_multiply_large();

  cout << "\n=== Тесты для binary_pow ===\n";
  test_binary_pow_zero_one();
  test_binary_pow_two();
  test_binary_pow_small();
  test_binary_pow_large_exp();
  test_binary_pow_mod_properties();

  cout << "\n=== Тесты для devide ===\n";
  test_devide_basic();
  test_devide_by_self();
  test_devide_inverse();
  test_devide_large();
  test_devide_roundtrip();

  cout << "\n✅ Все тесты пройдены!\n";
  return 0;
}

#include "../prime_numbers.h"
#include <cassert>
#include <iostream>

using namespace std;

void test_sieve_basic() {
  cout << "Testing sieve_of_eratosthenes()...\n";

  vector<bool> is_prime = sieve_of_eratosthenes(20);

  // Проверяем известные простые числа до 20
  vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
  for (int p : primes) {
    assert(is_prime[p]);
  }

  // Проверяем известные составные числа
  vector<int> composites = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20};
  for (int c : composites) {
    assert(!is_prime[c]);
  }

  cout << "✓ sieve_of_eratosthenes PASSED\n";
}

void test_prime_factorization() {
  cout << "Testing prime_factorization()...\n";

  // 12 = 2^2 * 3
  auto factors = prime_factorization(12);
  assert(factors.size() == 2);
  assert(factors[0] == make_pair(2, 2));
  assert(factors[1] == make_pair(3, 1));

  // 17 простое число
  factors = prime_factorization(17);
  assert(factors.size() == 1);
  assert(factors[0] == make_pair(17, 1));

  cout << "✓ prime_factorization PASSED\n";
}

void test_is_prime() {
  cout << "Testing is_prime()...\n";

  assert(is_prime(2) == true);
  assert(is_prime(3) == true);
  assert(is_prime(5) == true);
  assert(is_prime(17) == true);

  assert(is_prime(1) == false);
  assert(is_prime(4) == false);
  assert(is_prime(9) == false);
  assert(is_prime(15) == false);

  cout << "✓ is_prime PASSED\n";
}

void test_gcd_lcm() {
  // gcd
  assert(gcd_ll(0, 0) == 0);
  assert(gcd_ll(0, 5) == 5);
  assert(gcd_ll(5, 0) == 5);
  assert(gcd_ll(54, 24) == 6);
  assert(gcd_ll(-54, 24) == 6);
  assert(gcd_ll(-54, -24) == 6);
  assert(gcd_ll(17, 13) == 1);

  // lcm (std::lcm)
  assert(lcm_ll(0, 0) == 0);
  assert(lcm_ll(0, 5) == 0);
  assert(lcm_ll(6, 8) == 24);
  assert(lcm_ll(21, 6) == 42);
  assert(lcm_ll(-21, 6) == 42);
  assert(lcm_ll(-21, -6) == 42);

  // Свойство: gcd(a,b) * lcm(a,b) == |a*b| (для ненулевых, без переполнения)
  {
    ll a = 12, b = 18;
    ll g = gcd_ll(a, b);
    ll l = lcm_ll(a, b);
    assert(g == 6);
    assert(l == 36);
    assert(g * l == a * b);
  }
}

int main() {
  cout << "\n=== PRIME NUMBERS TESTS ===\n\n";

  test_sieve_basic();
  test_prime_factorization();
  test_is_prime();
  test_gcd_lcm();

  cout << "\n✓✓✓ ALL PRIME NUMBERS TESTS PASSED ✓✓✓\n\n";
  return 0;
}

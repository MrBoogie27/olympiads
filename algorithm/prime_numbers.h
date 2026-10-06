#include <numeric>
#include <vector>

using namespace std;
typedef long long ll;

// Проверка, является ли число простым
bool is_prime(int n) {
  if (n < 2) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }

  return true;
}

// Простое решето Эратосфена - находит все простые числа до n
vector<bool> sieve_of_eratosthenes(int n) {
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;

  for (int i = 2; i * i <= n; i++) {
    if (is_prime[i]) {
      for (int j = i * i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }

  return is_prime;
}

// Получить простую факторизацию числа n
// Возвращает вектор пар (простое число, степень)
vector<pair<int, int>> prime_factorization(int n) {
  vector<pair<int, int>> factors;

  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      int cnt = 0;
      while (n % i == 0) {
        cnt++;
        n /= i;
      }
      factors.push_back({i, cnt});
    }
  }

  if (n > 1) {
    factors.push_back({n, 1});
  }

  return factors;
}

// Функция Эйлера φ(n) - количество чисел от 1 до n, взаимно простых с n
ll euler_phi(const vector<pair<int, int>>& factors) {
  ll result = 1;
  for (const auto& [p, cnt] : factors) {
    result *= (p - 1);
    for (int i = 1; i < cnt; i++) {
      result *= p;
    }
  }
  return result;
}

// Вспомогательная функция для НОД (наибольший общий делитель)
ll gcd_ll(ll a, ll b) {
  // std::gcd корректно работает с отрицательными, возвращает неотрицательный результат
  return std::gcd(a, b);
}

// Вспомогательная функция для НОК (наименьшее общее кратное)
ll lcm_ll(ll a, ll b) {
  // std::lcm тоже возвращает неотрицательный результат; lcm(0, x) = 0
  return std::lcm(a, b);
}

// TODO:
// Линейное решето Эратосфена - O(n) вместо O(n log log n)
// Также вычисляет наименьший простой делитель (spf - smallest prime factor)
// vector<int> linear_sieve(int n, vector<int>& spf)
// Быстрая факторизация с использованием линейного решета
// vector<pair<int, int>> fast_factorization(int n, const vector<int>& spf)

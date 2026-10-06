#include "modulo_algebra.h"

using namespace std;
typedef long long ll;

// ============== Комбинаторика ==============

const int MAXN = 1e5 + 5;

// Факториалы и их обратные (для работы с модульной арифметикой)
ll fact[MAXN];
ll inv_fact[MAXN];

// Модульный обратный элемент (используя малую теорему Ферма)
ll mod_inverse(ll a) { return binary_pow(a, MOD - 2); }

// Предварительное вычисление факториалов и их обратных
void precompute_factorials(int n) {
  fact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = (fact[i - 1] * i) % MOD;
  }

  inv_fact[n] = mod_inverse(fact[n]);
  for (int i = n - 1; i >= 0; i--) {
    inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
  }
}

// ============== Сочетания (Combinations) ==============

// C(n, k) = n! / (k! * (n-k)!) - количество способов выбрать k элементов из n.
// 0 ≤ k ≤ n C(n, k) с модулем (требует precompute_factorials)
ll binomial_mod(int n, int k) {
  if (k > n || k < 0)
    return 0;
  if (k == 0 || k == n)
    return 1;

  return (fact[n] * inv_fact[k] % MOD) * inv_fact[n - k] % MOD;
}

// Треугольник Паскаля (динамическое программирование)
// dp[i][j] = C(i, j) для всех j ≤ K ≤ n, i ≤ n
// K - ограничение сверху для столбца k (если K не указан, K = n)
vector<vector<ll>> pascals_triangle(int n, int K = -1) {
  if (K == -1)
    K = n;       // По умолчанию K = n
  K = min(K, n); // K не может быть больше n

  vector<vector<ll>> dp(n + 1, vector<ll>(K + 1, 0));

  for (int i = 0; i <= n; i++) {
    dp[i][0] = 1;
    int limit = min(i, K);
    for (int j = 1; j <= limit; j++) {
      dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
    }
  }

  return dp;
}

// ============== Перестановки (Permutations) ==============

// P(n, k) = n! / (n-k)! - количество упорядоченных выборов k элементов из n
// P(n, k) с модулем (требует precompute_factorials)
ll permutation_mod(int n, int k) {
  if (k > n || k < 0)
    return 0;
  if (k == 0)
    return 1;

  return (fact[n] * inv_fact[n - k]) % MOD;
}

// ============== Сочетания с повторениями ==============

// Количество способов выбрать k элементов из n с повторениями
// H(n, k) = C(n + k - 1, k)
ll combinations_with_repetition_mod(int n, int k) {
  if (n == 0 && k == 0)
    return 1;
  if (n == 0)
    return 0;

  return binomial_mod(n + k - 1, k);
}

// ============== Перестановки с повторениями ==============

// Количество перестановок n элементов, где есть повторения
// Если cnt[i] = количество элементов типа i, то:
// P = n! / (cnt[0]! * cnt[1]! * ... * cnt[k]!)
ll permutations_with_repetition_mod(int n, const vector<int> &cnt) {
  ll result = fact[n];

  for (int c : cnt) {
    result = (result * inv_fact[c]) % MOD;
  }

  return result;
}

// ============== Каталанские числа (Catalan Numbers) ==============

// C(n) = C(2n, n) / (n + 1) = (2n)! / ((n+1)! * n!)
// Применение: количество скобочных последовательностей, путей в сетке и т.д.
// Каталанские числа с модулем
ll catalan_mod(int n) {
  if (n == 0)
    return 1;

  ll num = binomial_mod(2 * n, n);
  ll denom = mod_inverse(n + 1);

  return (num * denom) % MOD;
}

// C(n) = sum(C(i) * C(n - 1 - i)), 0 ≤ i < n
// Динамическое программирование для каталанских чисел
vector<ll> catalan_dp(int n) {
  vector<ll> cat(n + 1, 0);
  cat[0] = cat[1] = 1;

  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      cat[i] = (cat[i] + cat[j] * cat[i - 1 - j]) % MOD;
    }
  }

  return cat;
}

// ============== Белловские числа (Bell Numbers) ==============

// B(n) = sum(C(n - 1, i) * B(i)), 0 ≤ i < n
// Применение: количество способов разбить множество из n элементов на
// подмножества Вычисляется через треугольник Белла
vector<ll> bell_numbers(int n) {
  vector<vector<ll>> bell(n + 1);
  bell[0].assign({1});

  for (int i = 1; i <= n; i++) {
    bell[i].assign(i + 1, 0);
    bell[i][0] = bell[i - 1][i - 1];
    for (int j = 1; j <= i; j++) {
      bell[i][j] = (bell[i][j - 1] + bell[i - 1][j - 1]) % MOD;
    }
  }

  vector<ll> result(n + 1);
  for (int i = 0; i <= n; i++) {
    result[i] = bell[i][0];
  }

  return result;
}

// ============== Числа Стирлинга (Stirling Numbers) ==============

// S(n, k) - число способов разбить множество n элементов на k непустых
// подмножеств S(n, k) = S(n - 1, k - 1) + k * S(n - 1, k) B(n) = sum(S(n, i)),
// 0 ≤ i ≤ n (числа Стирлинга второго рода)
vector<vector<ll>> stirling_second(int n, int K = -1) {
  if (K == -1)
    K = n;       // По умолчанию K = n
  K = min(K, n); // K не может быть больше n

  vector<vector<ll>> dp(n + 1, vector<ll>(K + 1, 0));
  dp[0][0] = 1;

  for (int i = 1; i <= n; i++) {
    int limit = min(i, K);
    for (int j = 1; j <= limit; j++) {
      dp[i][j] = (dp[i - 1][j - 1] + j * dp[i - 1][j] % MOD) % MOD;
    }
  }

  return dp;
}

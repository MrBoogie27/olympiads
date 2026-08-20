#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// TEMPLATE - Полезный шаблон для быстрого старта на Codeforces
// ============================================================================

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ld EPS = 1e-9;
const ld PI = acos(-1);

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define yes cout << "YES\n"
#define no cout << "NO\n"

// ============================================================================
// ПОЛЕЗНЫЕ ФУНКЦИИ
// ============================================================================

// GCD
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// LCM
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

// Быстрое возведение в степень
ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// Проверка простоты
bool isPrime(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Факторизация
vector<ll> factorize(ll n) {
    vector<ll> factors;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.pb(i);
            n /= i;
        }
    }
    if (n > 1) factors.pb(n);
    return factors;
}

// Префиксные суммы
vector<ll> prefixSum(vector<ll>& arr) {
    vector<ll> pref(arr.size() + 1, 0);
    for (int i = 0; i < arr.size(); i++) {
        pref[i + 1] = pref[i] + arr[i];
    }
    return pref;
}

// Запрос суммы на диапазоне [l, r]
ll rangeSum(vector<ll>& pref, int l, int r) {
    return pref[r + 1] - pref[l];
}

// ============================================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================================================

void solve() {
    // Ваше решение здесь
    int n;
    cin >> n;
    vi arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Пример: вывести сумму всех элементов
    ll sum = 0;
    for (int x : arr) sum += x;
    cout << sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t = 1;
    // cin >> t; // раскомментируйте, если несколько тестов
    
    while (t--) {
        solve();
    }
    
    return 0;
}

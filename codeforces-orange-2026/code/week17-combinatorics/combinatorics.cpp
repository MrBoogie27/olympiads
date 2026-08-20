#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

long long fact[MAXN], inv_fact[MAXN];

long long power(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void precompute(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    inv_fact[n] = power(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
    }
}

long long nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return fact[n] * inv_fact[r] % MOD * inv_fact[n-r] % MOD;
}

long long nPr(int n, int r) {
    if (r > n || r < 0) return 0;
    return fact[n] * inv_fact[n-r] % MOD;
}

int main() {
    precompute(MAXN - 1);
    
    cout << "C(5,2) = " << nCr(5, 2) << "\n";
    cout << "P(5,2) = " << nPr(5, 2) << "\n";
    
    return 0;
}

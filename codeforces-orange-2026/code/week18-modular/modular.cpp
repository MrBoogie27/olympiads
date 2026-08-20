#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

long long power(long long a, long long b, long long mod) {
    long long res = 1; a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long modInverse(long long a, long long mod) {
    return power(a, mod - 2, mod);
}

int main() {
    cout << "2^10 mod 1e9+7 = " << power(2, 10, MOD) << "\n";
    cout << "Inverse of 3 mod 1e9+7 = " << modInverse(3, MOD) << "\n";
    return 0;
}

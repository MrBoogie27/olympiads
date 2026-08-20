#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MOD = 998244353;

ll multiply(ll x, ll y) {
  return (x * y) % MOD;
}

ll binary_pow(ll x, ll pow) {
  ll answer = 1;

  for (; pow > 0; pow >>= 1, x = multiply(x, x)) {
    if (pow & 1) {
      answer = multiply(answer, x);
    }
  }

  return answer;
}

ll devide(ll x, ll y) {
  return (x * binary_pow(y, MOD - 2)) % MOD;
}

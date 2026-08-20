#include <bits/stdc++.h>
using namespace std;

int mobius[1000005];

void computeMobius(int n) {
    mobius[1] = 1;
    vector<bool> is_prime(n + 1, true);
    
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i; j <= n; j += i) {
                is_prime[j] = false;
                if (mobius[j] != 0 || j == i) {
                    mobius[j] = -mobius[j];
                }
            }
        }
    }
}

int main() {
    computeMobius(10);
    for (int i = 1; i <= 10; i++) {
        cout << "mu(" << i << ") = " << mobius[i] << "\n";
    }
    return 0;
}

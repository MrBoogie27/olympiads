#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 3;
    vector<int> dp(1 << n, 0);
    
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                dp[mask] += i + 1;
            }
        }
    }
    
    for (int mask = 0; mask < (1 << n); mask++) {
        cout << "Mask " << mask << ": " << dp[mask] << "\n";
    }
    
    return 0;
}

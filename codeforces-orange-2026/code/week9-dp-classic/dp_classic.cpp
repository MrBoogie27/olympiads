#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 0/1 рюкзак (Knapsack)
ll knapsack01(vector<int>& weights, vector<int>& values, int capacity) {
    int n = weights.size();
    vector<ll> dp(capacity + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    
    return dp[capacity];
}

// Неограниченный рюкзак (Unbounded Knapsack)
ll unboundedKnapsack(vector<int>& weights, vector<int>& values, int capacity) {
    vector<ll> dp(capacity + 1, 0);
    
    for (int w = 1; w <= capacity; w++) {
        for (int i = 0; i < weights.size(); i++) {
            if (weights[i] <= w) {
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
    }
    
    return dp[capacity];
}

// Longest Increasing Subsequence (LIS)
int lis(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}

// LIS за O(n log n)
int lisOptimized(vector<int>& arr) {
    vector<int> lis;
    
    for (int x : arr) {
        auto it = lower_bound(lis.begin(), lis.end(), x);
        if (it == lis.end()) {
            lis.push_back(x);
        } else {
            *it = x;
        }
    }
    
    return lis.size();
}

// Longest Common Subsequence (LCS)
int lcs(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[m][n];
}

// Минимальное количество монет
int minCoins(vector<int>& coins, int target) {
    vector<int> dp(target + 1, INT_MAX);
    dp[0] = 0;
    
    for (int i = 1; i <= target; i++) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[target] == INT_MAX ? -1 : dp[target];
}

// Количество способов получить сумму
ll countWays(vector<int>& coins, int target) {
    vector<ll> dp(target + 1, 0);
    dp[0] = 1;
    
    for (int coin : coins) {
        for (int i = coin; i <= target; i++) {
            dp[i] += dp[i - coin];
        }
    }
    
    return dp[target];
}

// Числа Фибоначчи (с DP)
ll fibonacci(int n) {
    if (n <= 1) return n;
    
    vector<ll> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Тест 1: 0/1 рюкзак
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    cout << "0/1 Knapsack (capacity=8): " << knapsack01(weights, values, 8) << "\n";
    
    // Тест 2: LIS
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS length: " << lisOptimized(arr) << "\n";
    
    // Тест 3: LCS
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";
    cout << "LCS length: " << lcs(s1, s2) << "\n";
    
    // Тест 4: Минимальное количество монет
    vector<int> coins = {1, 2, 5};
    cout << "Min coins for 5: " << minCoins(coins, 5) << "\n";
    
    // Тест 5: Количество способов
    cout << "Ways to get sum 5: " << countWays(coins, 5) << "\n";
    
    return 0;
}

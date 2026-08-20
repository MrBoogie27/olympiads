#include <bits/stdc++.h>
using namespace std;

// Префиксная функция для KMP
vector<int> computePrefix(string s) {
    int n = s.length();
    vector<int> pi(n, 0);
    
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    
    return pi;
}

// KMP: поиск всех вхождений паттерна
vector<int> kmp(string text, string pattern) {
    vector<int> pi = computePrefix(pattern);
    vector<int> result;
    
    int j = 0;
    for (int i = 0; i < text.length(); i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) j++;
        
        if (j == pattern.length()) {
            result.push_back(i - pattern.length() + 1);
            j = pi[j - 1];
        }
    }
    
    return result;
}

// Количество вхождений паттерна
int countOccurrences(string text, string pattern) {
    return kmp(text, pattern).size();
}

// Наименьший период строки
int findPeriod(string s) {
    vector<int> pi = computePrefix(s);
    int n = s.length();
    
    if (pi[n - 1] == 0) return n;
    if (n % (n - pi[n - 1]) == 0) {
        return n - pi[n - 1];
    }
    return n;
}

// Префикс-палиндром
int longestPrefixPalindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    
    vector<int> pi = computePrefix(s + "#" + rev);
    return pi.back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string text = "AABAACAADAABAABA";
    string pattern = "AABA";
    
    vector<int> occurrences = kmp(text, pattern);
    cout << "KMP search for '" << pattern << "' in '" << text << "':\n";
    cout << "Positions: ";
    for (int pos : occurrences) {
        cout << pos << " ";
    }
    cout << "\n";
    
    cout << "Count: " << occurrences.size() << "\n";
    
    string s = "abab";
    cout << "Period of '" << s << "': " << findPeriod(s) << "\n";
    
    return 0;
}

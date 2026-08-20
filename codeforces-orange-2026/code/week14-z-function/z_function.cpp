#include <bits/stdc++.h>
using namespace std;

// Z-функция
vector<int> zFunction(string s) {
    int n = s.length();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    
    return z;
}

// Поиск всех вхождений паттерна
vector<int> findOccurrences(string text, string pattern) {
    string s = pattern + "#" + text;
    vector<int> z = zFunction(s);
    
    vector<int> result;
    int patLen = pattern.length();
    
    for (int i = patLen + 1; i < s.length(); i++) {
        if (z[i] == patLen) {
            result.push_back(i - patLen - 1);
        }
    }
    
    return result;
}

// Количество различных подстрок
int countDistinctSubstrings(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    
    string combined = s + "#" + rev;
    vector<int> z = zFunction(combined);
    
    int n = s.length();
    set<string> distinct;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            distinct.insert(s.substr(i, j - i + 1));
        }
    }
    
    return distinct.size();
}

// Периодическая строка (най least period)
int findPeriod(string s) {
    vector<int> z = zFunction(s);
    int n = s.length();
    
    for (int i = 1; i < n; i++) {
        if (z[i] + i == n && n % i == 0) {
            return i;
        }
    }
    
    return n;
}

// Наименьший период циклического сдвига
int minimalCyclicShift(string s) {
    string doubled = s + s;
    vector<int> z = zFunction(doubled);
    
    for (int i = 1; i < s.length(); i++) {
        if (z[i] == s.length() - i) {
            return i;
        }
    }
    
    return s.length();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Тест 1: Z-функция
    string s = "aaabaab";
    vector<int> z = zFunction(s);
    cout << "Z-function of '" << s << "': ";
    cout << "0 ";
    for (int i = 1; i < z.size(); i++) {
        cout << z[i] << " ";
    }
    cout << "\n";
    
    // Тест 2: Поиск паттерна
    string text = "abcabdabcabcabab";
    string pattern = "abcab";
    vector<int> occurrences = findOccurrences(text, pattern);
    cout << "Occurrences of '" << pattern << "' in '" << text << "': ";
    for (int pos : occurrences) {
        cout << pos << " ";
    }
    cout << "\n";
    
    // Тест 3: Период
    string periodic = "abcabcabc";
    cout << "Period of '" << periodic << "': " << findPeriod(periodic) << "\n";
    
    // Тест 4: Минимальный циклический сдвиг
    string cyclic = "abcd";
    cout << "Minimal cyclic shift of '" << cyclic << "': " << minimalCyclicShift(cyclic) << "\n";
    
    return 0;
}

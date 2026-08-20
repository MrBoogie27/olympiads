#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
const long long BASE = 31;

long long computeHash(string s) {
    long long hash_val = 0;
    long long pow_base = 1;
    
    for (char c : s) {
        hash_val = (hash_val + (c - 'a' + 1) * pow_base) % MOD;
        pow_base = (pow_base * BASE) % MOD;
    }
    
    return hash_val;
}

int main() {
    string s1 = "abc";
    string s2 = "abc";
    string s3 = "abd";
    
    cout << "Hash of 'abc': " << computeHash(s1) << "\n";
    cout << "Hash of 'abc': " << computeHash(s2) << "\n";
    cout << "Hash of 'abd': " << computeHash(s3) << "\n";
    
    return 0;
}

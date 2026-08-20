#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    static const int MAXN = 1000005;
    static const int SIGMA = 26;
    
    int next[MAXN][SIGMA], fail[MAXN], cnt;
    int val[MAXN];
    
    AhoCorasick() {
        cnt = 0;
        memset(next[0], -1, sizeof(next[0]));
        memset(val, 0, sizeof(val));
    }
    
    void insert(string s, int id) {
        int u = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (next[u][ch] == -1) {
                next[u][ch] = ++cnt;
                memset(next[cnt], -1, sizeof(next[cnt]));
            }
            u = next[u][ch];
        }
        val[u] = id;
    }
    
    void build() {
        queue<int> q;
        fail[0] = 0;
        
        for (int i = 0; i < SIGMA; i++) {
            if (next[0][i] == -1) {
                next[0][i] = 0;
            } else {
                fail[next[0][i]] = 0;
                q.push(next[0][i]);
            }
        }
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (val[fail[u]]) val[u] = val[fail[u]];
            
            for (int i = 0; i < SIGMA; i++) {
                if (next[u][i] == -1) {
                    next[u][i] = next[fail[u]][i];
                } else {
                    fail[next[u][i]] = next[fail[u]][i];
                    q.push(next[u][i]);
                }
            }
        }
    }
    
    vector<int> query(string text) {
        vector<int> result(256, 0);
        int u = 0;
        
        for (char c : text) {
            int ch = c - 'a';
            u = next[u][ch];
            if (val[u]) result[val[u]]++;
        }
        
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    AhoCorasick ac;
    ac.insert("he", 1);
    ac.insert("she", 2);
    ac.insert("his", 3);
    ac.insert("hers", 4);
    ac.build();
    
    string text = "ushers";
    vector<int> res = ac.query(text);
    
    cout << "Occurrences in '" << text << "':\n";
    for (int i = 1; i <= 4; i++) {
        if (res[i]) cout << "Pattern " << i << ": " << res[i] << "\n";
    }
    
    return 0;
}

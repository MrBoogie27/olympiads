#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Binary Indexed Tree (Fenwick Tree)
class BIT {
private:
    vector<ll> tree;
    int n;
    
public:
    BIT(int size) {
        n = size + 1;
        tree.resize(n, 0);
    }
    
    // Добавить val к элементу с индексом idx (1-indexed)
    void update(int idx, ll val) {
        for (int i = idx; i < n; i += i & (-i)) {
            tree[i] += val;
        }
    }
    
    // Получить префиксную сумму до idx (1-indexed)
    ll query(int idx) {
        ll sum = 0;
        for (int i = idx; i > 0; i -= i & (-i)) {
            sum += tree[i];
        }
        return sum;
    }
    
    // Получить сумму на диапазоне [l, r] (1-indexed)
    ll rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

// Fenwick Tree для значений
class FenwickTree {
private:
    vector<ll> tree;
    vector<ll> arr;
    int n;
    
    void updateDiff(int idx, ll val) {
        for (int i = idx; i <= n; i += i & (-i)) {
            tree[i] += val;
        }
    }
    
    ll queryDiff(int idx) {
        ll sum = 0;
        for (int i = idx; i > 0; i -= i & (-i)) {
            sum += tree[i];
        }
        return sum;
    }
    
public:
    FenwickTree(int size) {
        n = size;
        tree.resize(n + 1, 0);
        arr.resize(n + 1, 0);
    }
    
    // Установить значение (1-indexed)
    void set(int idx, ll val) {
        ll diff = val - arr[idx];
        arr[idx] = val;
        updateDiff(idx, diff);
    }
    
    // Получить сумму [1, idx]
    ll query(int idx) {
        return queryDiff(idx);
    }
    
    // Получить сумму [l, r]
    ll rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

// Fenwick Tree с 2D поддержкой
class BIT2D {
private:
    vector<vector<ll>> tree;
    int rows, cols;
    
    void update(int r, int c, ll val) {
        for (int i = r; i <= rows; i += i & (-i)) {
            for (int j = c; j <= cols; j += j & (-j)) {
                tree[i][j] += val;
            }
        }
    }
    
    ll query(int r, int c) {
        ll sum = 0;
        for (int i = r; i > 0; i -= i & (-i)) {
            for (int j = c; j > 0; j -= j & (-j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }
    
public:
    BIT2D(int r, int c) {
        rows = r;
        cols = c;
        tree.resize(r + 1, vector<ll>(c + 1, 0));
    }
    
    void update(int r1, int c1, int r2, int c2, ll val) {
        update(r1, c1, val);
        update(r1, c2 + 1, -val);
        update(r2 + 1, c1, -val);
        update(r2 + 1, c2 + 1, val);
    }
    
    ll query(int r, int c) {
        return query(r, c);
    }
    
    ll rangeQuery(int r1, int c1, int r2, int c2) {
        return query(r2, c2) - query(r1 - 1, c2) - query(r2, c1 - 1) + query(r1 - 1, c1 - 1);
    }
};

// Fenwick Tree для поиска K-го элемента
class FenwickKth {
private:
    vector<ll> tree;
    int n;
    
public:
    FenwickKth(int size) {
        n = size;
        tree.resize(n + 1, 0);
    }
    
    void insert(int idx) {
        for (int i = idx; i <= n; i += i & (-i)) {
            tree[i]++;
        }
    }
    
    void remove(int idx) {
        for (int i = idx; i <= n; i += i & (-i)) {
            tree[i]--;
        }
    }
    
    // Найти K-й наименьший элемент
    int findKth(int k) {
        int lo = 1, hi = n, ans = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            ll sum = 0;
            for (int i = mid; i > 0; i -= i & (-i)) {
                sum += tree[i];
            }
            if (sum >= k) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Тест 1: Базовый BIT
    BIT bit(10);
    bit.update(1, 5);
    bit.update(3, 3);
    bit.update(5, 2);
    
    cout << "Sum [1, 5]: " << bit.rangeQuery(1, 5) << "\n";
    cout << "Sum [3, 5]: " << bit.rangeQuery(3, 5) << "\n";
    
    // Тест 2: Fenwick Tree
    FenwickTree ft(5);
    ft.set(1, 5);
    ft.set(2, 3);
    ft.set(3, 2);
    
    cout << "Range sum [1, 3]: " << ft.rangeQuery(1, 3) << "\n";
    
    // Тест 3: K-th элемент
    FenwickKth fk(5);
    fk.insert(1);
    fk.insert(3);
    fk.insert(5);
    
    cout << "2nd smallest inserted element at position: " << fk.findKth(2) << "\n";
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Сегментное дерево (Segment Tree)
class SegmentTree {
private:
    vector<ll> tree;
    int n;
    
    void build(vector<ll>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
    void updateHelper(int node, int start, int end, int idx, ll val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                updateHelper(2*node, start, mid, idx, val);
            } else {
                updateHelper(2*node+1, mid+1, end, idx, val);
            }
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
    ll queryHelper(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        ll p1 = queryHelper(2*node, start, mid, l, r);
        ll p2 = queryHelper(2*node+1, mid+1, end, l, r);
        return p1 + p2;
    }
    
public:
    SegmentTree(vector<ll>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    
    void update(int idx, ll val) {
        updateHelper(1, 0, n - 1, idx, val);
    }
    
    ll query(int l, int r) {
        return queryHelper(1, 0, n - 1, l, r);
    }
};

// Сегментное дерево для минимума
class SegmentTreeMin {
private:
    vector<ll> tree;
    int n;
    const ll INF = 1e18;
    
    void build(vector<ll>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = min(tree[2*node], tree[2*node+1]);
        }
    }
    
    void updateHelper(int node, int start, int end, int idx, ll val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                updateHelper(2*node, start, mid, idx, val);
            } else {
                updateHelper(2*node+1, mid+1, end, idx, val);
            }
            tree[node] = min(tree[2*node], tree[2*node+1]);
        }
    }
    
    ll queryHelper(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return INF;
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        ll p1 = queryHelper(2*node, start, mid, l, r);
        ll p2 = queryHelper(2*node+1, mid+1, end, l, r);
        return min(p1, p2);
    }
    
public:
    SegmentTreeMin(vector<ll>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    
    void update(int idx, ll val) {
        updateHelper(1, 0, n - 1, idx, val);
    }
    
    ll query(int l, int r) {
        return queryHelper(1, 0, n - 1, l, r);
    }
};

// Сегментное дерево с Lazy Propagation (для range update)
class SegmentTreeLazy {
private:
    vector<ll> tree, lazy;
    int n;
    
    void updateRange(int node, int start, int end, int l, int r, ll val) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0;
        }
        
        if (start > end || start > r || end < l) return;
        
        if (l <= start && end <= r) {
            tree[node] += (end - start + 1) * val;
            if (start != end) {
                lazy[2*node] += val;
                lazy[2*node+1] += val;
            }
            return;
        }
        
        int mid = (start + end) / 2;
        updateRange(2*node, start, mid, l, r, val);
        updateRange(2*node+1, mid+1, end, l, r, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    ll queryRange(int node, int start, int end, int l, int r) {
        if (start > end || start > r || end < l) return 0;
        
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0;
        }
        
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        ll p1 = queryRange(2*node, start, mid, l, r);
        ll p2 = queryRange(2*node+1, mid+1, end, l, r);
        return p1 + p2;
    }
    
public:
    SegmentTreeLazy(int size) {
        n = size;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }
    
    void updateRange(int l, int r, ll val) {
        updateRange(1, 0, n - 1, l, r, val);
    }
    
    ll queryRange(int l, int r) {
        return queryRange(1, 0, n - 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Тест 1: Сегментное дерево для суммы
    vector<ll> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);
    
    cout << "Sum [1, 3]: " << st.query(1, 3) << "\n";
    st.update(2, 10);
    cout << "After update arr[2]=10, Sum [1, 3]: " << st.query(1, 3) << "\n";
    
    // Тест 2: Сегментное дерево для минимума
    SegmentTreeMin stMin(arr);
    cout << "Min [1, 4]: " << stMin.query(1, 4) << "\n";
    
    // Тест 3: Lazy Propagation
    SegmentTreeLazy stLazy(6);
    stLazy.updateRange(1, 3, 5);
    cout << "Sum [1, 3] after range update (+5): " << stLazy.queryRange(1, 3) << "\n";
    
    return 0;
}

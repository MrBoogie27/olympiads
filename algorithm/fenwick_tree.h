#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

class FenwickTree {
public:
  explicit FenwickTree(int n)
    : tree(n, 0) { 
  }

  explicit FenwickTree(vector<int> a)
    : tree(a.size(), 0) {

    if (a.size() == 0) {
      return;
    }
    tree[0] = a[0];
    for (int i = 1; i < a.size(); i++) {
      tree[i] = tree[i - 1] + a[i];
    }

    for (int i = a.size() - 1; i > 0; i--) {
      int lower_i = (i & (i + 1)) - 1;
      if (lower_i >= 0) {
        tree[i] -= tree[lower_i];
      }
    }
  }

  void inc(int i, int delta) {
    for (; i < tree.size(); i |= (i + 1)) {
      tree[i] += delta;
    }
  }

  ll sum(int r) {
    ll res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) {
      res += tree[r];
    }
    return res;
  }

  ll sum(int l, int r) {
    return sum(r) - sum(l - 1);
  }

private:
  vector<ll> tree;
};

class Fenwick2DTree {
public:
  explicit Fenwick2DTree(int n, int m)
    : tree(n, vector<ll>(m, 0)) { 
  }

  void inc(int i, int j, int delta) {
    for (; i < tree.size(); i |= (i + 1)) {
      for (; j < tree[i].size(); j |= (j + 1)) {
        tree[i][j] += delta;
      }
    }
  }

  ll sum(int ry, int rx) {
    ll res = 0;
    for (; rx >= 0; rx = (rx & (rx + 1)) - 1) {
      for (; ry >= 0; ry = (ry & (ry + 1)) - 1) {
        res += tree[rx][ry];
      }
    }
    return res;
  }

  ll sum(int ly, int ry, int lx, int rx) {
    return sum(ry, rx) - sum(ry, rx - 1) + sum(ry - 1, rx - 1) - sum(ry - 1, rx);
  }

private:
  vector<vector<ll>> tree;
};

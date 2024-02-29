#include <bits/stdc++.h>
using namespace std;

struct item {
  long long sum = 0, pref = 0, suff = 0, sub = 0;
};

struct segtree {
  struct node {
    int l = 0, r = 0;
    item val;
    node(int _l = 0, int _r = 0) {
      l = _l, r = _r;
    }
  };
  int N = 1;
  vector<node> tree;
  segtree(int _n) {
    while(N < _n) N <<= 1;
    tree.resize(2 * N);
    build();
  }
  void build() {
    for (int i = 0; i < N; i++) {
      tree[i + N] = node(i, i + 1);
    }
    for (int i = N - 1; i > 0; i--) {
      tree[i] = node(tree[2 * i].l, tree[2 * i + 1].r);
    } 
  }
  item comb(item a, item b) {
    return {a.sum + b.sum, max(a.sum + b.pref, a.pref), max(b.sum + a.suff, b.suff), 
    max({a.sub, b.sub, a.suff + b.pref})};
  }
  void update(int i, long long v) {
    i += N;
    tree[i].val = {v, max(v, 0LL), max(v, 0LL), max(v, 0LL)};
    while (i > 1) {
      i >>= 1;
      tree[i].val = comb(tree[2 * i].val, tree[2 * i + 1].val);
    }
  }
  item query(int v, int l, int r) {
    if (l <= tree[v].l && tree[v].r <= r) {
      return tree[v].val;
    }
    if (tree[v].l >= r || tree[v].r <= l) {
      return {0, 0, 0, 0};
    }
    return comb(query(2 * v, l, r), query(2 * v + 1, l, r));
  }
  item query(int l, int r) {
    return query(1, l, r);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  segtree st(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    st.update(i, x);
  }
  for (int i = 0; i < q; i++) {
    int k, u;
    cin >> k >> u;
    st.update(k - 1, u);
    cout << st.query(0, n).sub << '\n';
  }
  return 0;
}

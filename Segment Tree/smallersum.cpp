#include <bits/stdc++.h>
using namespace std;

struct node {
  int l, r;
  vector<int> vals;
  vector<long long> pref;
  node(int _l = 0, int _r = 0) {
    l = _l, r = _r;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int N = 1;
  while (N < n) {
    N <<= 1;
  }
  vector<node> tree(2 * N);
  for (int i = 0; i < N; i++) {
    tree[N + i] = node(i, i + 1);
    tree[N + i].vals = {a[i]};
    tree[N + i].pref = {0, a[i]};
  }
  for (int i = N - 1; i > 0; i--) {
    tree[i] = node(tree[2 * i].l, tree[2 * i + 1].r);
    tree[i].vals = tree[2 * i].vals;
    for (int other : tree[2 * i + 1].vals) {
      tree[i].vals.push_back(other);
    }
    sort(tree[i].vals.begin(), tree[i].vals.end());
    tree[i].pref = {0};
    for (int v : tree[i].vals) {
      tree[i].pref.push_back(tree[i].pref.back() + v);
    }
  }
  auto query = [&](int v, int l, int r, int x, auto&& self) -> long long {
    if (l <= tree[v].l && tree[v].r <= r) {
      int up = upper_bound(tree[v].vals.begin(), tree[v].vals.end(), x) - tree[v].vals.begin();
      return tree[v].pref[up];
    }
    if (l >= tree[v].r || r <= tree[v].l) {
      return 0;
    }
    return self(2 * v, l, r, x, self) + self(2 * v + 1, l, r, x, self);
  };
  int q;
  cin >> q;
  long long prev = 0;
  while (q--) {
    long long l, r, x;
    cin >> l >> r >> x;
    l ^= prev;
    r ^= prev;
    x ^= prev;
    long long ans = query(1, l - 1, r, x, query);
    cout << ans << '\n';
    prev = ans;
  }
  return 0;
}

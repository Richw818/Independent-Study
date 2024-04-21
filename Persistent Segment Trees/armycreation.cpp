#include <bits/stdc++.h>
using namespace std;

struct node {
  int val;
  int lc, rc;
};

struct psegtree {
  vector<node> tree;
  int n;
  psegtree(int _n) {
    n = _n;
  }
  int comb(int a, int b) {
    return a + b;
  }
  int newLeaf(int v) {
    int p = tree.size();
    node nd = {v, 0, 0};
    tree.push_back(nd);
    return p;
  }
  int newParent(int left, int right) {
    int p = tree.size();
    node nd = {comb(tree[left].val, tree[right].val), left, right};
    tree.push_back(nd);
    return p;
  }
  int build(vector<int>& sum, int lo, int hi) {
    if (lo == hi) {
      return newLeaf(sum[lo]);
    }
    int mid = (lo + hi) / 2;
    return newParent(build(sum, lo, mid), build(sum, mid + 1, hi));
  }
  int build(vector<int>& sum) {
    return build(sum, 0, n - 1);
  }
  int update(int i, int x, int p, int lo, int hi) {
    if (lo == hi) {
      return newLeaf(x);
    }
    int mid = (lo + hi) / 2;
    int lc = tree[p].lc, rc = tree[p].rc;
    if (i <= mid) {
      return newParent(update(i, x, lc, lo, mid), rc);
    } else {
      return newParent(lc, update(i, x, rc, mid + 1, hi));
    }
  }
  int update(int p, int i, int x) {
    return update(i, x, p, 0, n - 1);
  }
  int query(int p, int l, int r, int lo, int hi) {
    if (l <= lo && hi <= r) {
      return tree[p].val;
    }
    if (hi < l || lo > r) {
      return 0;
    }
    int lc = tree[p].lc, rc = tree[p].rc;
    int mid = (lo + hi) / 2;
    return comb(query(lc, l, r, lo, mid), query(rc, l, r, mid + 1, hi));
  }
  int query(int p, int l, int r) {
    return query(p, l, r, 0, n - 1);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  map<int, vector<int>> inds;
  vector<pair<int, int>> upds;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    int to = (int) inds[a[i]].size() - k;
    if (to < 0) {
      upds.emplace_back(-1, i);
    } else {
      upds.emplace_back(inds[a[i]][to], i);
    }
    inds[a[i]].push_back(i);
  }
  vector<int> z(n);
  psegtree pst(n);
  int start_root = pst.build(z);
  sort(upds.begin(), upds.end());
  vector<int> roots(n);
  for (int i = 0; i < n; i++) {
    int prev_root = (i == 0 ? start_root : roots[i - 1]);
    roots[i] = pst.update(prev_root, upds[i].second, 1);
  }
  int prev = 0, q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    l = (l + prev) % n + 1;
    r = (r + prev) % n + 1;
    if (l > r) {
      swap(l, r);
    }
    l--, r--;
    int lo = 0, hi = n;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (upds[mid].first < l) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    int ans = 0;
    if (lo > 0) {
      int p = roots[lo - 1];
      ans = pst.query(p, l, r); 
    }
    cout << ans << '\n';
    prev = ans;
  }
  return 0;
}

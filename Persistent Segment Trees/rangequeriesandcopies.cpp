#include <bits/stdc++.h>
using namespace std;

struct node {
  long long val;
  int lc, rc;
};

struct psegtree {
  vector<node> tree;
  int n;
  psegtree(int _n) {
    n = _n;
  }
  long long comb(long long a, long long b) {
    return a + b;
  }
  int newLeaf(long long v) {
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
  int build(vector<long long>& sum, int lo, int hi) {
    if (lo == hi) {
      return newLeaf(sum[lo]);
    }
    int mid = (lo + hi) / 2;
    return newParent(build(sum, lo, mid), build(sum, mid + 1, hi));
  }
  int build(vector<long long>& sum) {
    return build(sum, 0, n - 1);
  }
  int update(int i, long long x, int p, int lo, int hi) {
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
  int update(int p, int i, long long x) {
    return update(i, x, p, 0, n - 1);
  }
  long long query(int p, int l, int r, int lo, int hi) {
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
  long long query(int p, int l, int r) {
    return query(p, l, r, 0, n - 1);
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr); 
  int n, q;
  cin >> n >> q;
  vector<long long> t(n);
  for (int i = 0; i < n; i++) {
    cin >> t[i];
  }
  psegtree pst(n);
  vector<int> roots = {pst.build(t)};
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int k, a, x;
      cin >> k >> a >> x;
      a--, k--;
      roots[k] = pst.update(roots[k], a, x);
    } else if (type == 2) {
      int k, a, b;
      cin >> k >> a >> b;
      k--, a--, b--;
      cout << pst.query(roots[k], a, b) << '\n';
    } else {
      int k;
      cin >> k;
      k--;
      roots.push_back(roots[k]);
    }
  }
  return 0;
}

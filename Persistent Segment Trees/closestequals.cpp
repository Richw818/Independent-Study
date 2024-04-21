#include <bits/stdc++.h>
using namespace std;
 
const int N = 1.1e7, INF = 1e9;
 
struct node {
  int val;
  int lc, rc;
};
 
struct psegtree {
  node tree[N];
  int n, cn = 0;
  psegtree(int _n) {
    n = _n;
  }
  int comb(int a, int b) {
    return min(a, b);
  }
  int newLeaf(int v) {
    int p = cn++;
    node nd = {v, 0, 0};
    tree[p] = nd;
    return p;
  }
  int newParent(int left, int right) {
    int p = cn++;
    node nd = {comb(tree[left].val, tree[right].val), left, right};
    tree[p] = nd;
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
      return INF;
    }
    int lc = tree[p].lc, rc = tree[p].rc;
    int mid = (lo + hi) / 2;
    return comb(query(lc, l, r, lo, mid), query(rc, l, r, mid + 1, hi));
  }
  int query(int p, int l, int r) {
    return query(p, l, r, 0, n - 1);
  }
};
 
struct upd {
  int ans, left;
  int id;
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  map<int, int> ind;
  vector<upd> upds;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (ind.count(a[i])) {
      upds.push_back({i - ind[a[i]], ind[a[i]], i});
    } else {
      upds.push_back({INF, -1, i});
    }
    ind[a[i]] = i;
  }
  sort(upds.begin(), upds.end(), [](const upd& a, const upd& b) {
    return a.left < b.left;
  });
  vector<int> start(n, INF);
  psegtree pst(n);
  int start_root = pst.build(start);
  vector<int> roots(n);
  for (int i = n - 1; i >= 0; i--) {
    int r = (i == n - 1 ? start_root : roots[i + 1]);
    roots[i] = pst.update(r, upds[i].id, upds[i].ans);
  }
  while (q--) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    int lo = 0, hi = n;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (upds[mid].left < l) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    if (lo == n) {
      cout << -1 << '\n';
    } else {
      int ans = pst.query(roots[lo], l, r);
      cout << (ans == INF ? -1 : ans) << '\n';
    }
  }
  return 0;
}

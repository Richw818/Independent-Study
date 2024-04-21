#include <bits/stdc++.h>
using namespace std;

template <const int MOD>
struct modint {
  int val;
  modint() { val = 0; }
  modint(const long long& v) {
    val = v % MOD;
    if (val < 0) val += MOD;
  }

  friend ostream& operator<<(ostream& os, const modint& a) { return os << a.val; }
  friend bool operator==(const modint& a, const modint& b) { return a.val == b.val; }
  friend bool operator!=(const modint& a, const modint& b) { return !(a == b); }
  friend bool operator<(const modint& a, const modint& b) { return a.val < b.val; }

  modint operator-() const { return modint(-val); }
  modint& operator+=(const modint& other) {
    val += other.val;
    if (val >= MOD) val -= MOD;
    return *this;
  }
  modint& operator-=(const modint& other) {
    val -= other.val;
    if (val < 0) val += MOD;
    return *this;
  }
  modint& operator*=(const modint& other) {
    val = (int) ((1LL * val * other.val) % MOD);
    return *this;
  }
  modint& operator++() {
    val++;
    if (val == MOD) val = 0;
    return *this;
  }
  modint& operator--() {
    if (val == 0) val = MOD;
    val--;
    return *this;
  }
  friend modint modpow(modint a, long long p) {
    modint res = 1;
    for (; p; p >>= 1, a *= a) {
      if (p & 1) res *= a;
    }
    return res;
  }
  friend modint inv(const modint& a) { return modpow(a, MOD - 2); }
  modint& operator/=(const modint& other) { return (*this) *= inv(other); }

  friend modint operator+(modint a, const modint& b) { return a += b; }
  friend modint operator-(modint a, const modint& b) { return a -= b; }
  friend modint operator*(modint a, const modint& b) { return a *= b; }
  friend modint operator/(modint a, const modint& b) { return a /= b; }
  friend modint operator++(modint& a, int) { modint r = a; ++a; return r; }
  friend modint operator--(modint& a, int) { modint r = a; --a; return r; }

  operator long long() const { return val; }
};

struct dsu {
  int N;
  vector<int> p, s;
  dsu(int _n) {
    N = _n;
    p.resize(N); s.resize(N);
    iota(p.begin(), p.end(), 0);
    fill(s.begin(), s.end(), 1);
  }
  int size(int a) {
    return s[find(a)];
  }
  int find(int a) {
    if(p[a] == a) return a;
    p[a] = find(p[a]);
    return p[a];
  }
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    if(s[a] > s[b]) swap(a, b);
    s[b] += s[a];
    p[a] = b;
    return true;
  }
  bool same(int a, int b) {
    return find(a) == find(b);
  }
};

using mint = modint<(int) 1e9 + 9>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, k;
  cin >> n >> m >> k;
  vector<pair<int, int>> edges;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    edges.emplace_back(u, v);
  }
  vector<mint> f(1 << m);
  for (int mask = 0; mask < (1 << m); mask++) {
    dsu d(n);
    int comps = n;
    for (int i = 0; i < m; i++) {
      if (mask & (1 << i)) {
        comps -= d.unite(edges[i].first, edges[i].second);
      }
    }
    f[mask] = modpow(mint(k), comps);
  }
  for (int i = 0; i < m; i++) {
    for (int mask = 0; mask < (1 << m); mask++) {
      if (~mask & (1 << i)) {
        f[mask] -= f[mask ^ (1 << i)];
      }
    }
  }
  vector<mint> ans(m + 1);
  for (int mask = 0; mask < (1 << m); mask++) {
    ans[__builtin_popcount(mask)] += f[mask];
  }
  for (int i = 0; i <= m; i++) {
    cout << ans[i] << " \n"[i == m];
  }
  return 0;
}

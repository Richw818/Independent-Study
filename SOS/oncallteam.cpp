#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  int inv = (1 << m) - 1;
  vector<int> masks(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      if (s[j] == '1') {
        masks[i] ^= (1 << j);
      }
    }
  }
  vector<int> sub(1 << m);
  for (int i = 0; i < n; i++) {
    sub[masks[i]]++;
  }
  for (int i = 0; i < m; i++) {
    for (int mask = 0; mask < (1 << m); mask++) {
      if ((1 << i) & mask) {
        sub[mask] += sub[mask ^ (1 << i)];
      }
    }
  }
  vector<int> diff(1 << m);
  for (int mask = 0; mask < (1 << m); mask++) {
    diff[mask] = n - sub[mask ^ inv] - __builtin_popcount(mask);
  }
  for (int i = 0; i < m; i++) {
    for (int mask = 0; mask < (1 << m); mask++) {
      if ((1 << i) & mask) {
        diff[mask] = min(diff[mask], diff[mask ^ (1 << i)]);
      }
    }
  }
  vector<bool> ok(m + 1, true);
  for (int mask = 0; mask < (1 << m); mask++) {
    if (diff[mask] < 0) {
      ok[__builtin_popcount(mask)] = false;
    }
  }
  int ans = 0;
  for (int i = 1; i <= m; i++) {
    if (ok[i]) {
      ans = i;
    }
  }
  cout << ans << '\n';
  return 0;
}

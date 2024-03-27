#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  const int N = 24;
  int n;
  cin >> n;
  vector<int> f(1 << N);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    int k = s.size();
    for (int mask = 1; mask < (1 << k); mask++) {
      int actualMask = 0;
      for (int b = 0; b < k; b++) {
        if ((1 << b) & mask) {
          actualMask |= (1 << (s[b] - 'a'));
        }
      }
      if (__builtin_popcount(mask) % 2) {
        f[actualMask]++;
      } else {
        f[actualMask]--;
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int mask = 0; mask < (1 << N); mask++) {
      if (mask & (1 << i)) {
        f[mask] += f[mask ^ (1 << i)];
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < (1 << N); i++) {
    ans ^= f[i] * f[i];
  }
  cout << ans << '\n';
  return 0;
}

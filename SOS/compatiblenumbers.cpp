#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  const int N = 22;
  vector<int> f(1 << N, -1);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    f[a[i]] = a[i];
  }
  for (int i = 0; i < N; i++) {
    for (int mask = 0; mask < (1 << N); mask++) {
      if (mask & (1 << i)) {
        f[mask] = max(f[mask], f[mask ^ (1 << i)]);
      }
    }
  }
  int inv = (1 << N) - 1;
  for (int i = 0; i < n; i++) {
    cout << f[a[i] ^ inv] << " \n"[i == n - 1];
  }
  return 0;
}

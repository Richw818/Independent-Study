#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, w;
  cin >> n >> w;
  if (w == 1) {
    cout << n << '\n';
    return 0;
  }
  vector<int> a(n), b(w);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < w; i++) {
    cin >> b[i];
  }
  vector<int> diffs;
  for (int i = 1; i < w; i++) {
    diffs.push_back(b[i] - b[i - 1]);
  }
  for (int i = 1; i < n; i++) {
    diffs.push_back(a[i] - a[i - 1]);
  }
  n--, w--;
  vector<int> z(n + w);
  int l = 0, r = 0;
  for (int i = 1; i < n + w; i++) {
    if (i < r) {
      z[i] = min(r - i, z[i - l]);
    }
    while (i + z[i] < n + w && diffs[i + z[i]] == diffs[z[i]]) {
      z[i]++;
    }
    if (i + z[i] > r) {
      r = i + z[i];
      l = i;
    }
  }
  int ans = 0;
  for (int i = w; i < n + w; i++) {
    if (z[i] >= w) {
      ans++;
    }
  }
  cout << ans << '\n';
  return 0;
}

#include <bits/stdc++.h>
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s, t;
  cin >> s >> t;
  int n = s.size(), m = t.size();
  t += s;
  vector<int> z(n + m);
  int l = 0, r = 0, ans = 0;
  for (int i = 1; i < n + m; i++) {
    if (i <= r) {
      z[i] = min(r - i, z[i - l]);
    }
    while (i + z[i] < n + m && t[i + z[i]] == t[z[i]]) {
      z[i]++;
    }
    if (i + z[i] > r) {
      r = i + z[i];
      l = i;
    }
    if (i >= m && z[i] >= m) {
      ans++;
    }
  }
  cout << ans << '\n';
  return 0;
}

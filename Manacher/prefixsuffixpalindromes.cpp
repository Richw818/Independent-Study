#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    int n = s.size();
    int match = 0, l = 0, r = n - 1;
    while (l < n && r >= 0 && s[l] == s[r]) {
      match++;
      l++, r--;
    }
    if (l == n) {
      cout << s << '\n';
      continue;
    }
    vector<vector<int>> p(2, vector<int>(n));
    for (int type = 0; type < 2; type++) {
      l = -1, r = 0;
      for (int i = 0; i < n; i++) {
        if (i < r) {
          p[type][i] = min(r - i, p[type][l + r - i]);
        }
        while (i - p[type][i] >= 0 && i + p[type][i] + !type < n && s[i - p[type][i]] == s[i + p[type][i] + !type]) {
          p[type][i]++;
        }
        if (i + p[type][i] > r) {
          r = i + p[type][i];
          l = i - p[type][i];
        } 
      }
    }
    int bestTotal = 0, start = -1, mid = -1;
    for (int type = 0; type < 2; type++) {
      for (int i = 0; i < n; i++) {
        int need = min(i - p[type][i] + 1, n - i - p[type][i] - !type);
        if (match >= need) {
          int total = 2 * need + 2 * p[type][i] - type;
          if (total > bestTotal) {
            bestTotal = total;
            start = i - p[type][i] + 1;
            mid = 2 * p[type][i] - type;
          }
        }
      }
    }
    int need = min(start, n - start - mid);
    string ans = s.substr(0, need) + s.substr(start, mid) + s.substr(n - need, need);
    cout << ans << '\n';
  }
  return 0;
}

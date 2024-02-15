#include <bits/stdc++.h>
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  int n = s.size();
  vector<vector<int>> p(2, vector<int>(n));
  for (int type = 0; type < 2; type++) {
    int l = -1, r = 0;
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
  int start = -1, mx = 0;
  for (int type = 0; type < 2; type++) {
    for (int i = 0; i < n; i++) {
      if (2 * p[type][i] - type > mx) {
        mx = 2 * p[type][i] - type;
        start = i - p[type][i] + 1;
      }
    }
  }
  cout << s.substr(start, mx) << '\n';
  return 0;
}

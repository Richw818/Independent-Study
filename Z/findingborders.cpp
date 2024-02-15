#include <bits/stdc++.h>
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  int n = s.size();
  vector<int> z(n), cands;
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    if (i <= r) {
      z[i] = min(r - i, z[i - l]);
    }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
      z[i]++;
    }
    if (i + z[i] > r) {
      r = i + z[i];
      l = i;
    }
    if (i + z[i] == n) {
      cands.push_back(n - i);
    }
  }
  reverse(cands.begin(), cands.end());
  int k = cands.size();
  for (int i = 0; i < k; i++) {
    cout << cands[i] << " \n"[i == k - 1];
  }
  return 0;
}

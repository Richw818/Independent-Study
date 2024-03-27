#include <bits/stdc++.h>
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  const int N = 20;
  vector<int> a(1 << N);
  int n;
  cin >> n;
  vector<int> x(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i];
    a[x[i]]++;
  }
  vector<int> sub = a, sup = a;
  for (int i = 0; i < N; i++) {
    for (int mask = 0; mask < (1 << N); mask++) {
      if (mask & (1 << i)) {
        sub[mask] += sub[mask ^ (1 << i)];
      } else {
        sup[mask] += sup[mask ^ (1 << i)];
      }
    }
  }
  int other = (1 << N) - 1;
  for (int i = 0; i < n; i++) {
    cout << sub[x[i]] << ' ' << sup[x[i]] << ' ' << n - sub[x[i] ^ other] << '\n';
  }
  return 0;
}

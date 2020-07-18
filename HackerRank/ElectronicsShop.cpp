// AC #Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
void program() {
  int b, n, m;
  cin >> b >> n >> m;
  vector<int> keys, drives;
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    keys.push_back(x);
  }
  for (int i = 1, x; i <= m; ++i) {
    cin >> x;
    drives.push_back(x);
  }
  sort(keys.begin(), keys.end());
  sort(drives.begin(), drives.end());
  int ans = 0;
  if (keys[0] + drives[0] > b)
    ans = -1;
  else {
    reverse(keys.begin(), keys.end());
    for (int i = 0, j = 0; i < keys.size(); ++i) {
      for (; j < drives.size(); ++j) {
        if (keys[i] + drives[j] > b)
          break;
        ans = max(ans, keys[i] + drives[j]);
      }
    }
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}

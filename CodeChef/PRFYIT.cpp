// AC DP Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e3
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
string s;
int n;
int dp[BUFF(N_MAX)][2];
int getCount(bool type, int l, int r) {
  if (r == 0 || l == n + 1)
    return 0;
  return dp[r][type] - dp[l - 1][type];
}
int solve() {
  int ret = N_MAX;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      for (int k = 0; k < 2; ++k)
        ret = min(ret, getCount(k, 1, i - 1) + getCount(!k, i, j) + getCount(k, j + 1, n));
    }
  }
  return ret;
}
void program() {
  cin >> s;
  n = s.size();
  for (int i = 0; s[i]; ++i) {
    dp[i + 1][0] = dp[i][0];
    dp[i + 1][1] = dp[i][1];
    if (s[i] == '1')
      ++dp[i + 1][1];
    else ++dp[i + 1][0];
  }
  cout << solve() << endl;
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--)
    program();
  return 0;
}
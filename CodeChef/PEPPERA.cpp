// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 150
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n;
string s[BUFF(N_MAX)];
pii dp[BUFF(N_MAX)][2];
bool ans[BUFF(N_MAX)][2];
int m_diff(pii x) { return abs(x.first - x.second); }
void compute() {
  int fh, sh;
  pii x, y;
  for (int i = 1; i <= n; ++i) {
    fh = sh = 0;
    for (int j = 0; j <= (n / 2) - 1; ++j) {
      fh += s[i][j] == '1';
      sh += s[i][j + n] == '1';
    }
    x.first = fh + dp[i - 1][0].first;
    x.second = sh + dp[i - 1][0].second;
    y.first = fh + dp[i - 1][1].first;
    y.second = sh + dp[i - 1][1].second;
    if (m_diff(x) <= m_diff(y)) {
      dp[i][0] = x;
      ans[i][0] = false;
    } else {
      dp[i][0] = y;
      ans[i][0] = true;
    }
    swap(fh, sh);
    x.first = fh + dp[i - 1][0].first;
    x.second = sh + dp[i - 1][0].second;
    y.first = fh + dp[i - 1][1].first;
    y.second = sh + dp[i - 1][1].second;
    if (m_diff(x) <= m_diff(y)) {
      dp[i][1] = x;
      ans[i][1] = false;
    } else {
      dp[i][1] = y;
      ans[i][1] = true;
    }
  }
  dp[n + 1][0] = dp[n + 1][1] = { 0, 0 };
  if (m_diff(dp[n][0]) > m_diff(dp[n][1]))
    ans[n + 1][0] = ans[n + 1][1] = true;
}
void program() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> s[i];
  compute();
  for (int i = 1, det; i <= n; ++i) {
    if (m_diff(dp[i + 1][0]) < m_diff(dp[i + 1][1]))
      det = ans[i + 1][0];
    else det = ans[i + 1][1];
    if (det)
      reverse(begin(s[i]), end(s[i]));
    cout << s[i] << endl;
  }
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
// AC Knapsack, Bitset
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
bitset<BUFF(N_MAX * N_MAX)> dp[BUFF(N_MAX)];
int fh[BUFF(N_MAX)], sh[BUFF(N_MAX)];
void program() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> s[i];
  dp[0][0] = 1;
  int total = 0;
  for (int i = 1; i <= n; ++i) {
    fh[i] = sh[i] = 0;
    for (int j = 0, k = n / 2; j < n / 2; ++j, ++k) {
      fh[i] += s[i][j] == '1';
      sh[i] += s[i][k] == '1';
    }
    total += fh[i] + sh[i];
    dp[i] = dp[i - 1] << fh[i] | dp[i - 1] << sh[i];
  }
  int best = total / 2;
  while (!dp[n][best])
    --best;
  for (int i = n; i >= 1; --i) {
    if (best - fh[i] >= 0 && dp[i - 1][best - fh[i]]) {
      best -= fh[i];
    } else {
      reverse(begin(s[i]), end(s[i]));
      best -= sh[i];
    }
  }
  for (int i = 1; i <= n; ++i)
    cout << s[i] << endl;
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
// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 5000
#define MOD (ll) (1e9 + 7)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, a, b, k;
ll ans;
ll dp[2][BUFF(N_MAX)];
ll dp2[2][BUFF(N_MAX)];
bool previous, cur;
void fillCurDP() {
  dp[cur][0] = 0;
  for (int i = 1; i <= n + 1; ++i) {
    dp[cur][i] %= MOD;
    dp[cur][i] = (dp[cur][i] + dp[cur][i - 1]) % MOD;
    dp[!cur][i] = 0;
    if (dp[cur][i] < 0)
      printf("\n");
  }
}
void resetCur() {
  for (int i = 1; i <= n; ++i)
    dp2[cur][i] = 0;
}
int t_abs(int x) { return x >= 0 ? x : -x; }
void solve() {
  int x, l, r;
  dp[cur][a] = 1;
  dp2[cur][a] = 1;
  for (int i = 1; i <= k; ++i) {
    previous = cur;
    cur = !cur;
    resetCur();
    for (int j = 1; j <= n; ++j) {
      x = t_abs(j - b);
      l = max(1, j - x + 1);
      r = min(n + 1, j + x - 1);
      for (int m = l; m <= r; ++m) {
        if (m != j) {
          dp2[cur][m] += dp2[previous][j];
          dp2[cur][m] %= MOD;
        }
      }
      dp[cur][l] += dp[previous][j];
      dp[cur][j] -= dp[previous][j];
      dp[cur][j + 1] += dp[previous][j];
      dp[cur][r + 1] -= dp[previous][j];
    }
    fillCurDP();
    for (int j = 1; j <= n; ++j)
      if (dp[cur][j] != dp2[cur][j])
        printf("\n");
  }
  for (int i = 1; i <= n; ++i)
    ans = (ans + dp2[cur][i]) % MOD;
}
void program() {
  scanf("%d %d %d %d", &n, &a, &b, &k);
  solve();
  printf("%lld\n", ans);
}
int main() {
  program();
  return 0;
}
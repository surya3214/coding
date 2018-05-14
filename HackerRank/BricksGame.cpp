// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
using namespace std;
typedef long long int ll;
int n;
int bricks[BUFF(N_MAX)];
ll dp[BUFF(N_MAX)];
ll compute(int idx, bool player) {
  ll sum = 0;
  if (idx + 2 >= n) {
    if (player) {
      for (int i = idx; i <= n; i++) sum += bricks[i];
      return sum;
    } else return 0;
  }
  if (player && dp[idx] != -1) return dp[idx];
  ll ans = 1e15;
  for (int i = 1; i <= 3 && (idx + i - 1) <= n; i++) {
    if (player) {
      sum += bricks[idx + i - 1];
      dp[idx] = max(dp[idx], sum + compute(idx + i, !player));
    } else ans = min(ans, compute(idx + i, !player));
  }
  if (player) return dp[idx];
  else return ans;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  while (tcase--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &bricks[i]);
      dp[i] = -1;
    }
    printf("%lld\n", compute(1, true));
  }
}
int main() {
  freopen("HackerRank/BricksGame_input.txt", "r", stdin);
  program();
  return 0;
}
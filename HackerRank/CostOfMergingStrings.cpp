// AC                        
#include <iostream>
#include <cstdio>
#define N_MAX 360
#define INF 1E9
using namespace std;
char a[N_MAX], b[N_MAX];
int n, m, k;
int dp[N_MAX][N_MAX][N_MAX];
int solve(int a_pt, int b_pt, int k) {
  if (!k)
    return 0;
  if (min(a_pt + 1, b_pt + 1) < k)
    return INF;
  if (dp[a_pt][b_pt][k] != -1)
    return dp[a_pt][b_pt][k];
  int cost = (a[a_pt] - 'a') ^ (b[b_pt] - 'a');
  return dp[a_pt][b_pt][k] = min(cost + solve(a_pt - 1, b_pt - 1, k - 1), min(solve(a_pt - 1, b_pt, k), solve(a_pt, b_pt - 1, k)));
}
void reset() {
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      for (int l = 0; l <= k; l++)
        dp[i][j][l] = -1;
}
void program() {
  scanf("%d %d %d", &n, &m, &k);
  reset();
  scanf("%s", a);
  scanf("%s", b);
  int ans = solve(n - 1, m - 1, k);
  if (ans >= INF)
    printf("-1\n");
  else printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
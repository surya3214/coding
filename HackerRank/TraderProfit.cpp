//
#include <iostream>
#include <cstdio>
#include <cstring>
#define K_MAX 12
#define N_MAX 35
using namespace std;
int k, n, ans;
int A[N_MAX];
int dp[N_MAX][K_MAX];
void computeDP() {
  for (int i = 0; i <= n; i++)
    dp[i][0] = 0;
  for (int i = 2; i <= n; i++) {
    for (int j = i - 1; j >= 1; j--) {
      if (A[i] > A[j]) {
        for (int l = 1; l <= k; l++) {
          if (dp[j - 1][l - 1] != -1) {
            dp[i][l] = max(dp[i][l], A[i] - A[j] + dp[j - 1][l - 1]);
            for (int m = 0; m <= l; m++)
              dp[i][l] = max(dp[i][l], dp[i][m]);
            ans = max(ans, dp[i][l]);
          }
        }
      }
    }
  }
}
void program() {
  int q;
  scanf("%d", &q);
  while (q--) {
    ans = 0;
    memset(dp, -1, sizeof(dp));
    scanf("%d", &k);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &A[i]);
    computeDP();
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
#define K_MAX 1000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, k, ans;
int dp[2][BUFF(K_MAX)];
bool not_prev;
void reset() {
  ans = not_prev = 0;
  for (int i = 1; i <= K_MAX; ++i)
    dp[0][i] = dp[1][i] = 0;
  dp[!not_prev][0] = 1;
}
void program() {
  int tcase, x;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &x);
      not_prev = !not_prev;
      for (int j = k; j >= 0; --j) {
        if (dp[not_prev][j]) {
          dp[!not_prev][j] = 1;
          if (j + x <= k) {
            dp[not_prev][j + x] = 1;
            ans = max(ans, j + x);
          }
        }
      }
    }
    printf("Scenario #%d: %d\n", t, ans);
  }
}
int main() {
  program();
  return 0;
}
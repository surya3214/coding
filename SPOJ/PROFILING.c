// AC
#include <stdio.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define MOD 1000000007
#define true 1
#define false 0
// #pragma GCC optimize "O4"
typedef int bool;
typedef long long int ll;
typedef unsigned long long int ull;
ll dp[BUFF(N_MAX)];
void preprocess() {
  dp[0] = 1;
  for (int i = 0; i <= N_MAX; ++i) {
    dp[i] %= MOD;
    dp[i + 1] += dp[i];
    dp[i + 2] += dp[i];
  }
}
void program() {
  int tcase, n, k, x;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &k);
    if (n == 0 && n == k) x = 1;
    else {
      if (k == 0) k = 2;
      x = (n - k >= 0) ? dp[n - k] : 0;
    }
    printf("%d\n", x);
  }
}
int main() {
  preprocess();
  program();
  return 0;
}
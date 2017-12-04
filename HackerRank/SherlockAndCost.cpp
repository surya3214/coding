// AC
#include <iostream>
#include <cstdio>
#define N_MAX 100010
#define B_MAX 110
using namespace std;
int b[N_MAX], n;
int dp[N_MAX][2]; // 0 picks the maximum; 1 picks the minimum
int mod(int x) {
  return x > 0 ? x : -x;
}
void compute() {
  dp[1][0] = dp[1][1] = 0;
  for (int i = 2; i <= n; i++) {
    dp[i][0] = max(dp[i - 1][1] + mod(b[i] - 1), dp[i - 1][0] + mod(b[i] - b[i - 1]));
    dp[i][1] = max(dp[i - 1][0] + mod(b[i - 1] - 1), dp[i - 1][1] + mod(1 - 1));
  }
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &b[i]);
    compute();
    printf("%d\n", max(dp[n][0], dp[n][1]));
  }
}
int main() {
  program();
  return 0;
}
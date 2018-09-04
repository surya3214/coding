// AC DP
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define K_MAX 100
#define INF 1e9
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, k;
int dp[BUFF(K_MAX)];
void reset() {
  for (int i = 1; i <= k; ++i)
    dp[i] = INF;
}
void process(int price, int size) {
  if (price == -1) return;
  for (int i = 0; i + size <= k; ++i) {
    if (dp[i] != INF)
      dp[i + size] = min(dp[i + size], dp[i] + price);
  }
}
void program() {
  int tcase, val;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &k, &k);
    reset();
    for (int i = 1; i <= k; ++i) {
      scanf("%d", &val);
      process(val, i);
    }
    if (dp[k] == INF)
      dp[k] = -1;
    printf("%d\n", dp[k]);
  }
}
int main() {
  program();
  return 0;
}
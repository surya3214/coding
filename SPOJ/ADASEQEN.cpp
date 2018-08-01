// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define CHARS_MAX 26
#define N_MAX 2000
using namespace std;
typedef long long int ll;
int n, m, ans;
int cost[BUFF(CHARS_MAX)];
char a[BUFF(N_MAX)], b[BUFF(N_MAX)];
int a_cost[BUFF(N_MAX)], b_cost[BUFF(N_MAX)];
int dp[BUFF(N_MAX)][BUFF(N_MAX)];
void compute() {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (a[i - 1] == b[j - 1]) {
        dp[i][j] = max(dp[i][j], )
      }
    }
  }
}
int getIndexFromChar(char x) { return x - 'a' + 1; }
void program() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= CHARS_MAX; ++i)
    printf("%d", &cost[i]);
  scanf("%s", a);
  scanf("%s", b);
  for (int i = 0; i < n; ++i)
    a_cost[i] = cost[getIndexFromChar(a[i])] + (i > 0) ? a_cost[i - 1] : 0;
  for (int i = 0; i < m; ++i)
    b_cost[i] = cost[getIndexFromChar(b[i])] + (i > 0) ? b_cost[i - 1] : 0;
  compute();
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
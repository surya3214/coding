// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define CHARS_MAX 26
#define N_MAX 2000
using namespace std;
typedef long long int ll;
int n, m;
int cost[BUFF(CHARS_MAX)];
char a[BUFF(N_MAX)], b[BUFF(N_MAX)];
int dp[BUFF(N_MAX)][BUFF(N_MAX)];
int getIndexFromChar(char x) { return x - 'a' + 1; }
int compute() {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (a[i - 1] == b[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + cost[getIndexFromChar(a[i - 1])];
      else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return dp[n][m];
}
void program() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= CHARS_MAX; ++i)
    scanf("%d", &cost[i]);
  scanf("%s", a);
  scanf("%s", b);
  printf("%d\n", compute());
}
int main() {
  program();
  return 0;
}
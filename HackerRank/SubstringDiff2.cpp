//
#include <iostream>
#include <cstdio>
#define MAX_N 1510
using namespace std;
int k, ans;
char a[MAX_N], b[MAX_N];
int dp[MAX_N][MAX_N];
void reset() {
  for (int i = 0; i < MAX_N; i++)
    for (int j = 0; j < MAX_N; j++)
      dp[i][j] = -1;
  ans = 0;
}
int find(int i, int j, int mismatch_so_far) {
  if (mismatch_so_far > k || i == -1 || j == -1)
    return 0;
  if (dp[i][j] != -1)
    return dp[i][j];
  if (a[i] == b[j])
    dp[i][j] = 1 + find(i - 1, j - 1, 0);
  else {
    if (k >= 1) {
      int len = find(i - 1, j - 1, mismatch_so_far + 1);
      // a[i - 1 - len...i - 1] === b[j - 1 - len...j - 1] & mismatch <= k
      if (len < k)
        dp[i][j] = 1 + len;
      else if (len == k)
        if (a[i - len] == b[j - len])
          dp[i][j] = 1 + len;
        else dp[i][j] = len;
    } else dp[i][j] = 0;
  }
  return dp[i][j];
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    reset();
    scanf("%d %s %s", &k, a, b);
    // printf("%d %s %s", k, a, b);
    for (int i = 0; a[i] != '\0'; i++)
      for (int j = 0; b[j] != '\0'; j++)
        ans = max(ans, find(i, j, 0));
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
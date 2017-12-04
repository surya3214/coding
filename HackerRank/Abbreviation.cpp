// AC
#include <iostream>
#include <cstdio>
#include <cstring>
#define N_MAX 1010
using namespace std;
char a[N_MAX], b[N_MAX];
int dp[N_MAX][N_MAX];
bool upperCase(char a) {
  return (a >= 'A' && a <= 'Z') ? true : false;
}
bool possible(int x, int y) {
  if (x == -1 && y == -1)
    return true;
  if (x < y || (y == -1 && upperCase(a[x])))
    return false;
  if (y == -1) {
    if (possible(x - 1, y))
      return true;
    return false;
  }
  if (dp[x][y] != -1)
    return dp[x][y];
  if (upperCase(a[x])) {
    // you have to take this
    if (a[x] == b[y]) {
      if (possible(x - 1, y - 1))
        return dp[x][y] = true;
    }
  } else {
    if ((a[x] - 'a' + 'A') == b[y])
      if (possible(x - 1, y - 1))
        return dp[x][y] = true;
    if (possible(x - 1, y))
      return dp[x][y] = true;
  }
  return dp[x][y] = false;
}
void reset() {
  for (int i = 0; i < N_MAX; i++)
    for (int j = 0; j < N_MAX; j++)
      dp[i][j] = -1;
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%s", a);
    scanf("%s", b);
    reset();
    if (possible(strlen(a) - 1, strlen(b) - 1))
      printf("YES\n");
    else printf("NO\n");
  }
}
int main() {
  program();
  return 0;
}
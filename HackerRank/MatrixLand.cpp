//
#include <iostream>
#include <cstdio>
#include <vector>
#define N_MAX 4000010
#define M_MAX 4000010
using namespace std;
// int grid[N_MAX][M_MAX];
// int dp[N_MAX][M_MAX];
int **dp, **grid, **mlv, **mrv, **mlvit, **mrvit;
int n, m;
// vector<int> dp[N_MAX][M_MAX];
// vector<int> grid[N_MAX][M_MAX]; 
// int mlv[N_MAX][M_MAX], mrv[N_MAX][M_MAX];
// int mlvit[N_MAX][M_MAX], mrvit[N_MAX][M_MAX];
void computeDP() {
  for (int i = 1; i <= n; i++)
    grid[i][0] = mlv[i][0] = mlvit[i][0] = grid[i][m + 1] =  mrv[i][m + 1] = mrvit[i][m + 1] = 0;
  for (int j = 1; j <= m; j++)
    dp[0][j] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      mlv[i][j] = max(0, mlv[i][j - 1] + grid[i][j - 1]);
      if (j == 1)
       mlvit[i][j] = dp[i - 1][j];
      else mlvit[i][j] = max(dp[i - 1][j] + mlv[i][j], mlvit[i][j - 1] + grid[i][j - 1]);
    }
    for (int j = m; j >= 1; j--) {
      mrv[i][j] = max(0, mrv[i][j + 1] + grid[i][j + 1]);
      if (j == m)
        mrvit[i][j] = dp[i - 1][j];
      else mrvit[i][j] = max(dp[i - 1][j] + mrv[i][j], mrvit[i][j + 1] + grid[i][j + 1]);
    }
    for (int j = 1; j <= m; j++)
      dp[i][j] = grid[i][j] + max(mlvit[i][j] + mrv[i][j], mlv[i][j] + mrvit[i][j]);
  }
}
void program() {
  scanf("%d %d", &n, &m);
  grid = new int*[n + 10];
  dp = new int*[n + 10];
  mlv = new int*[n + 10];
  mrv = new int*[n + 10];
  mlvit = new int*[n + 10];
  mrvit = new int*[n + 10];
  for (int i = 0; i <= n; i++) {
    grid[i] = new int[m + 10];
    dp[i] = new int[m + 10];
    mlv[i] = new int[m + 10];
    mrv[i] = new int[m + 10];
    mlvit[i] = new int[m + 10];
    mrvit[i] = new int[m + 10];
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      scanf("%d", &grid[i][j]);
  computeDP();
  int ans = dp[n][1];
  for (int j = 2; j <= m; j++)
    ans = max(ans, dp[n][j]);
  printf("%d\n", ans);
}
int main() {
  freopen("MatrixLand_input.txt", "r", stdin);
  program();
  return 0;
}
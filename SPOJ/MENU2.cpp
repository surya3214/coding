// AC
#include <iostream>
#include <cstdio>
#define K_MAX 25
#define M_MAX 110
#define N_MAX 55
using namespace std;
int k, n, m;
struct {
  float value;
  int from_day;
  int from_dish;
} dp[K_MAX][M_MAX][N_MAX];
struct {
  float value;
  int budget, dish;
} ans;
struct {
  int cost;
  int value;
} dishes[N_MAX];
void reset() {
  for (int i = 0; i < K_MAX; i++)
    for (int j = 0; j < M_MAX; j++)
      for (int l = 0; l < N_MAX; l++)
        dp[i][j][l].value = -1;
  dp[0][0][0].value = 0;
}
bool isBounded(int x, int y) {
  if (x >= 1 && x <= k && y >= 1 && y <= m)
    return true;
  return false;
}
void compute() {
  int next_x, next_y;
  float next_val;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < m; j++) {
      for (int l = 0; l <= n; l++) {
        if (dp[i][j][l].value >= 0.0) {
          // this state has been reached
          for (int p = 1; p <= n; p++) {
            if (p != l) {
              next_x = i + 1;
              next_y = j + dishes[p].cost;
              next_val = dp[i][j][l].value + dishes[p].value * 1.0;
              while (isBounded(next_x, next_y)) {
                if (dp[next_x][next_y][p].value < next_val) {
                  dp[next_x][next_y][p].value = next_val;
                  dp[next_x][next_y][p].from_day = i;
                  dp[next_x][next_y][p].from_dish = l;
                }
                next_x = next_x + 1;
                next_y = next_y + dishes[p].cost;
                next_val = dp[i][j][l].value + dishes[p].value * 1.5;
              }
            }
          }
        }
      }
    }
  }
}
void findOrder(int k, int m, int n) {
  if (k != 0) {
    int days = k - dp[k][m][n].from_day;
    findOrder(dp[k][m][n].from_day, m - (days * dishes[n].cost), dp[k][m][n].from_dish);
    while (days--)
      printf("%d ", n);
  }
}
void program() {
  scanf("%d %d %d", &k, &n, &m);
  while (k != 0) {
    ans.value = 0.0;
    reset();
    for (int i = 1; i <= n; i++)
      scanf("%d %d", &dishes[i].cost, &dishes[i].value);
    compute();
    for (int j = 1; j <= m; j++)
      for (int l = 1; l <= n; l++)
        if (dp[k][j][l].value > ans.value)
          ans.value = dp[k][j][l].value, ans.budget = j, ans.dish = l;
    printf("%0.1f\n", ans.value);
    if (ans.value != 0.0) {
      findOrder(k, ans.budget, ans.dish);
      printf("\n");
    }
    printf("\n");
    scanf("%d %d %d", &k, &n, &m);
  }
}
int main() {
  program();
  return 0;
}
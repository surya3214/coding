//
#include <iostream>
#include <cstdio>
#define MAX_K 25
#define MAX_M 110
#define MAX_N 55
#define INF -1
using namespace std;
int n, k, m;
float dp[MAX_K][MAX_M];
struct {
  int dish_id, times;
} last_cooked[MAX_K][MAX_M];
struct {
  int cost, benefit;
} dishes[MAX_N];
void reset() {
  for (int i = 0; i <= k; i++)
    for (int j = 0; j <= m; j++)
      dp[i][j] = INF;
  dp[0][0] = last_cooked[0][0].dish_id = last_cooked[0][0].times = 0;
}
void find(int day, int budget_id) {
  int cur_dish = last_cooked[day][budget_id].dish_id;
  if (day != 1)
    find(day - 1, budget_id - dishes[cur_dish].cost);
  printf("%d ", cur_dish);
}
void compute() {
  int new_dish_id, new_times, new_benefit, new_cost, last_budget;
  float max_benefit = -1;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j <= m; j++) {
      if (dp[i][j] != INF) {
        // this state has been reached
        for (int l = 1; l <= n; l++) {
          // cook any of the dishes now if within budget
          new_dish_id = l;
          new_cost = j + dishes[new_dish_id].cost;
          if (new_cost <= m) {
            if (last_cooked[i][j].dish_id == l) {
              // same dish has been cooked continuosly
              new_times = last_cooked[i][j].times + 1;
              if (new_times == 2) new_benefit = 0.5 * dishes[new_dish_id].benefit;
              else new_benefit = 0;
            } else {
              new_benefit = dishes[new_dish_id].benefit;
              new_times = 1;
            }
            if (dp[i + 1][new_cost] < dp[i][j] + new_benefit) {
              dp[i + 1][new_cost] = dp[i][j] + new_benefit;
              last_cooked[i + 1][new_cost].dish_id = new_dish_id;
              last_cooked[i + 1][new_cost].times = new_times;
            }
          }
        }
      }
    }
  }
  for (int i = 0; i <= m; i++) {
    if (dp[k][i] > max_benefit) {
      max_benefit = max(max_benefit, dp[k][i]);
      last_budget = i;
    }
  }
  if (max_benefit != -1) {
    printf("%.1f\n", dp[k][last_budget]);
    find(k, last_budget);
  } else printf("0.0\n");
  printf("\n");
}
void program() {
  scanf("%d %d %d", &k, &n, &m);
  while (n != 0) {
    reset();
    for (int i = 1; i <= n; i++)
      scanf("%d %d", &dishes[i].cost, &dishes[i].benefit);
    compute();
    scanf("%d %d %d", &k, &n, &m);
  }
}
int main() {
  program();
  return 0;
}
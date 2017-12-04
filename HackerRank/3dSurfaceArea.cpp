// AC
#include <iostream>
#include <cstdio>
#define H_MAX 110
#define W_MAX 110
#define A 1
#define MOVES 2
using namespace std;
int grid[H_MAX][W_MAX];
int n, m, ans;
int movex[] = {-1, 0}; // LEFT, UP
int movey[] = {0, -1};
bool isValid(int x, int y) {
  if (x >= 1 && x <= n && y >= 1 && y <= m)
    return true;
  return false;
}
int min(int a, int b) {
  return a < b ? a : b;
}
void program() {
  int nextx, nexty;
  scanf("%d %d", &n, &m);
  ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &grid[i][j]);
      ans += grid[i][j] * 4 * A * A + 2 * A * A;
      for (int k = 0; k < MOVES; k++) {
        nextx = i + movex[k];
        nexty = j + movey[k];
        if (isValid(nextx, nexty))
          ans -= 2 * min(grid[i][j], grid[nextx][nexty]) * A * A;
      }
    }
  }
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
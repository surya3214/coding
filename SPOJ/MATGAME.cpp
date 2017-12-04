// AC
#include <iostream>
#include <cstdio>
#define N_MAX 55
using namespace std;
int n, m;
int grid[N_MAX][N_MAX];
int getGrundy(int x) {
  int G = 0;
  for (int j = m; j >= 1; j--) {
    if (j == m)
      G = grid[x][j];
    else if (grid[x][j] > G)
      G = grid[x][j];
    else G = grid[x][j] - 1;
  }
  return G;
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        scanf("%d", &grid[i][j]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
      ans = ans ^ getGrundy(i);
    if (ans)
      printf("FIRST\n");
    else printf("SECOND\n");
  }
}
int main() {
  program();
  return 0;
}
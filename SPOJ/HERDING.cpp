// AC
#include <iostream>
#include <cstdio>
#define N_MAX 1010
using namespace std;
char grid[N_MAX][N_MAX];
bool visited[N_MAX][N_MAX];
int n, m;
bool isValidUnvisited(int x, int y) {
  if (x >= 0 && x < n && y >= 0 && y < m &&
      !visited[x][y])
      return true;
  return false;
}
void dfs(int i, int j) {
  visited[i][j] = true;
  switch(grid[i][j]) {
    case 'S':
      if (isValidUnvisited(i + 1, j))
        dfs(i + 1, j);
      break;
    case 'N':
      if (isValidUnvisited(i - 1, j))
        dfs(i - 1, j);
      break;
    case 'E':
      if (isValidUnvisited(i, j + 1))
        dfs(i, j + 1);
      break;
    case 'W':
      if (isValidUnvisited(i, j - 1))
        dfs(i, j - 1);
      break;
  }
  if (isValidUnvisited(i - 1, j) && grid[i - 1][j] == 'S')
    dfs(i - 1, j);
  if (isValidUnvisited(i + 1, j) && grid[i + 1][j] == 'N')
    dfs(i + 1, j);
  if (isValidUnvisited(i, j + 1) && grid[i][j + 1] == 'W')
    dfs(i, j + 1);
  if (isValidUnvisited(i, j - 1) && grid[i][j - 1] == 'E')
    dfs(i, j - 1);
}
void program() {
  int cnt = 0;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", grid[i]);
    for (int j = 0; grid[i][j] != '\0'; j++)
      visited[i][j] = false;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!visited[i][j]) {
        dfs(i, j);
        cnt++;
      }
    }
  }
  printf("%d\n", cnt);
}
int main() {
  program();
  return 0;
}
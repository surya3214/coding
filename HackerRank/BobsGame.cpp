// AC
#include <iostream>
#include <cstdio>
#define N_MAX 1010
#define MOVES 3
using namespace std;
char grid[N_MAX][N_MAX];
int grundy[N_MAX][N_MAX];
bool seen[MOVES];
int n;
int movex[] = {0, -1, -1};
int movey[] = {-1, 0, -1};
bool isValid(int x, int y) {
  if (x >= 1 && x <= n && y >= 1 && y <= n &&
      grid[x][y] != 'X')
    return true;
  return false;
}
int mex() {
  for (int i = 0; i < MOVES; i++)
    if (!seen[i])
      return i;
  return MOVES;
}
void calculateGrundy() {
  int next_x, next_y, ans, win;
  ans = win = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (grid[i][j] == 'X')
        continue; // mark this invalid
      else {
        seen[0] = seen[1] = seen[2] = false;
        for (int k = 0; k < MOVES; k++) {
          next_x = i + movex[k];
          next_y = j + movey[k];
          if (isValid(next_x, next_y))
            seen[grundy[next_x][next_y]] = true;
        }
        grundy[i][j] = mex();
        if (grid[i][j] == 'K')
          ans ^= grundy[i][j];
      }
    }
  }
  if (ans) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (grid[i][j] == 'K') {
          for (int k = 0; k < MOVES; k++) {
            next_x = i + movex[k];
            next_y = j + movey[k];
            if (isValid(next_x, next_y)) {
              if ((ans ^ grundy[i][j] ^ grundy[next_x][next_y]) == 0)
                win++;
            }
          }
        }
      }
    }
    printf("WIN %d\n", win);
  }
  else printf("LOSE\n");
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%s", grid[i] + 1);
    calculateGrundy();
  }
}
int main() {
  program();
  return 0;
}
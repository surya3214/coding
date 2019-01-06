// AC BFS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char grid[BUFF(N_MAX)][BUFF(N_MAX)];
bool visited[BUFF(N_MAX)][BUFF(N_MAX)];
int n, sx, sy, dx, dy;
int ans;
int moves_x[] = { -1, 0, 1,  0 }; // U, R, D, L
int moves_y[] = {  0, 1, 0, -1 };
struct N {
  int x, y, moves;
  N() {}
  N(int t_x, int t_y, int t_moves) : x(t_x), y(t_y), moves(t_moves) { visited[x][y] = true; }
};
bool isPossible(int x, int y) {
  if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] != 'X' && !visited[x][y])
    return true;
  return false;
}
queue<N> q;
void bfs() {
  int next_x, next_y;
  struct N t;
  for (q.push(N(sx, sy, 0)); !q.empty() && !ans; q.pop()) {
    t = q.front();
    if (t.x == dx && t.y == dy)
      ans = t.moves;
    else {
      for (int moves = 0; moves < 4; ++moves) {
        next_x = t.x;
        next_y = t.y;
        while (isPossible(next_x + moves_x[moves], next_y + moves_y[moves])) {
          next_x += moves_x[moves];
          next_y += moves_y[moves];
          q.push(N(next_x, next_y, t.moves + 1));
        }
      }
    }
  }
}
void program() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%s", grid[i]);
  scanf("%d %d %d %d", &sx, &sy, &dx, &dy);
  bfs();
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
// AC Biased BFS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define ROW_MAX 1000
#define COL_MAX 1000
#define Q_MAX ROW_MAX * COL_MAX
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int r, c;
char grid[BUFF(ROW_MAX)][BUFF(COL_MAX)];
int dist[BUFF(ROW_MAX)][BUFF(COL_MAX)];
struct {
  struct {
    int x, y;
  } c_ids[BUFF(ROW_MAX * COL_MAX)];
  int q_ptr;
} m_queue[2];
bool cur;
void reset() {
  for (int i = 0; i < r; ++i) {
    memset(grid[i], 0, sizeof(grid[i]));
    memset(dist[i], -1, sizeof(dist[i]));
  }
  cur = false;
  m_queue[0].q_ptr = m_queue[1].q_ptr = 0;
}
void addToQueue(bool type, int x, int y, int d) {
  if (dist[x][y] == -1 || dist[x][y] > d) {
    dist[x][y] = d;
    int pos = ++m_queue[type].q_ptr;
    m_queue[type].c_ids[pos].x = x;
    m_queue[type].c_ids[pos].y = y;
  }
}
bool isEmpty(bool type) {
  return (m_queue[type].q_ptr == 0);
}
void pop(bool type, int &a, int &b) {
  a = m_queue[type].c_ids[m_queue[type].q_ptr].x;
  b = m_queue[type].c_ids[m_queue[type].q_ptr].y;
  --m_queue[type].q_ptr;  
}
int moves_x[] = { 0, 1, -1, 0,  0 };
int moves_y[] = { 0, 0,  0, 1, -1 };
bool isPossible(int x, int y) {
  if (x >= 0 && x < r && y >= 0 && y < c)
    return true;
  return false;
}
void bfs() {
  addToQueue(cur, 0, 0, 0);
  int c_x, c_y;
  int next_x, next_y;
  bool next_q;
  while (!isEmpty(cur)) {
    while (!isEmpty(cur)) {
      pop(cur, c_x, c_y);
      for (int i = 1; i <= 4; ++i) {
        next_x = c_x + moves_x[i];
        next_y = c_y + moves_y[i];
        if (isPossible(next_x, next_y)) {
          next_q = (grid[c_x][c_y] == grid[next_x][next_y]) ? cur : !cur;
          addToQueue(next_q, next_x, next_y, dist[c_x][c_y] + (next_q != cur));
        }
      }
    }
    cur = !cur;
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &r, &c);
    reset();
    for (int i = 0; i < r; ++i)
      scanf("%s", grid[i]);
    bfs();
    printf("%d\n", dist[r - 1][c - 1]);
  }
}
int main() {
  program();
  return 0;
}
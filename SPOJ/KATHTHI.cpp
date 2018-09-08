// TLE
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define ROW_MAX 1000
#define COL_MAX 10000
#define Q_MAX ROW_MAX * COL_MAX
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int r, c;
int t_time;
struct {
  int time;
  bool in_queue[BUFF(COL_MAX)];
  int dist[BUFF(COL_MAX)];
  char map[BUFF(COL_MAX)];
} grid[BUFF(ROW_MAX)];
struct {
  int x, y;
} m_queue[BUFF(Q_MAX)];
int front, rear;
void reset() {
  ++t_time;
  front = rear = 0;
}
void sanitizeGrid(int i) {
  if (grid[i].time != t_time) {
    for (int j = 0; j < c; ++j) {
      grid[i].in_queue[j] = false;
      grid[i].dist[j] = -1;
    }
    grid[i].time = t_time;
  }
}
void t_mod(int &x) {
  if (x == Q_MAX)
    x = 0;
}
void addToQueue(int x, int y) {
  m_queue[rear].x = x;
  m_queue[rear].y = y;
  t_mod(++rear);
}
void pushToQueue(int x, int y, int dist) {
  sanitizeGrid(x);
  if (grid[x].dist[y] == -1 || grid[x].dist[y] > dist) {
    grid[x].dist[y] = dist;
    if (!grid[x].in_queue[y]) {
      addToQueue(x, y);
      grid[x].in_queue[y] = true;
    }
  }
}
bool isEmpty() { return front == rear; }
void pop() {
  grid[m_queue[front].x].in_queue[m_queue[front].y] = false;
  t_mod(++front);
}
int moves_x[] = { 1, -1,  0, 0 };
int moves_y[] = { 0,  0, -1, 1 };
bool isPossible(int x, int y) {
  if (x >= 0 && x < r && y >= 0 && y < c)
    return true;
  return false;
}
void bfs() {
  int c_x, c_y;
  int next_x, next_y;
  for (pushToQueue(0, 0, 0); !isEmpty(); pop()) {
    c_x = m_queue[front].x;
    c_y = m_queue[front].y;
    for (int i = 0; i <= 3; ++i) {
      next_x = c_x + moves_x[i];
      next_y = c_y + moves_y[i];
      if (isPossible(next_x, next_y) && grid[c_x].map[c_y] == grid[next_x].map[next_y])
        pushToQueue(next_x, next_y, grid[c_x].dist[c_y]);
    }
    for (int i = 0; i <= 3; ++i) {
      next_x = c_x + moves_x[i];
      next_y = c_y + moves_y[i];
      if (isPossible(next_x, next_y) && grid[c_x].map[c_y] != grid[next_x].map[next_y])
        pushToQueue(next_x, next_y, grid[c_x].dist[c_y] + 1);
    }
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d", &r, &c);
    for (int i = 0; i < r; ++i)
      scanf("%s", grid[i].map);
    bfs();
    printf("%d\n", grid[r - 1].dist[c - 1]);
  }
}
int main() {
  program();
  return 0;
}
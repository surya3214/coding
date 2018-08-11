// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define L_MAX 8
#define STATES_MAX L_MAX * L_MAX * L_MAX * L_MAX
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
struct {
  int type;
  int x, y;
} figure1, figure2;
struct Q {
  int x1, y1, x2, y2;
  int moves;
} m_queue[BUFF(STATES_MAX)];
int front, rear;
struct {
  int time;
} visited[BUFF(L_MAX)][BUFF(L_MAX)][BUFF(L_MAX)][BUFF(L_MAX)];
int t_time;
void reset() {
  ++t_time;
  front = rear = 0;
}
void pushToQueue(int x1, int y1, int x2, int y2, int moves) {
  if (visited[x1][y1][x2][y2].time == t_time) return;
  m_queue[rear].x1 = x1;
  m_queue[rear].y1 = y1;
  m_queue[rear].x2 = x2;
  m_queue[rear].y2 = y2;
  m_queue[rear].moves = moves;
  ++rear;
  visited[x1][y1][x2][y2].time = t_time;
}
bool isEmpty() { return front == rear; }
void pop() { ++front; }
bool isPossible(int x, int y) {
  if (x >= 0 && x < L_MAX && y >= 0 && y < L_MAX) return true;
  return false;
}
struct M {
  int x, y;
} moves1[BUFF(4 * L_MAX)], moves2[BUFF(4 * L_MAX)];
void addMoves(int x, int y, struct M *t, int &cnt) {
  if (isPossible(x, y)) {
    ++cnt;
    t[cnt].x = x;
    t[cnt].y = y;
  }
}
int kings_x[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
int kings_y[] = { -1,  0,  1, -1, 1, -1, 0, 1 };
int knight_x[] = { -2, -2, -1, -1,  1, 1,  2, 2 };
int knight_y[] = { -1,  1, -2,  2, -2, 2, -1, 2 };
int generateMoves(int c_x, int c_y, bool type) {
  struct M *t;
  int f_type;
  if (type) t = moves1, f_type = figure1.type;
  else t = moves2, f_type = figure2.type;
  int cnt = 0;
  addMoves(c_x, c_y, t, cnt);
  if (type == 0) { // king
    for (int i = 0; i < L_MAX; ++i)
      addMoves(c_x + kings_x[i], c_y + kings_y[i], t, cnt);
  } else if (type == 1) { // knight
    for (int i = 0; i < L_MAX; ++i)
      addMoves(c_x + knight_x[i], c_y + knight_y[i], t, cnt);
  }
  if (type == 3 || type == 2) { // tower or queen
    for (int y = 0; y < L_MAX; ++y)
      addMoves(c_x, y, t, cnt);
    for (int x = 0; x < L_MAX; ++x)
      addMoves(x, c_y, t, cnt);
  }
  if (type == 4 || type == 2) { // bishop or queen
    for (int x = c_x - 1, y = c_y - 1; x >= 0 && y >= 0; --x, --y)
      addMoves(x, y, t, cnt);
    for (int x = c_x + 1, y = c_y + 1; x < L_MAX && y < L_MAX; ++x, ++y)
      addMoves(x, y, t, cnt);
    for (int x = c_x + 1, y = c_y - 1; x < L_MAX && y >= 0; ++x, --y)
      addMoves(x, y, t, cnt);
    for (int x = c_x - 1, y = c_y + 1; x >= 0 && y < L_MAX; --x, ++y)
      addMoves(x, y, t, cnt);
  }
  return cnt;
}
int bfs() {
  struct Q *t;
  int c1, c2;
  while (!isEmpty()) {
    t = &m_queue[front];
    if (t->x1 == t->x2 && t->y1 == t->y2) return t->moves;
    c1 = generateMoves(t->x1, t->y1, true);
    c2 = generateMoves(t->x2, t->y2, false);
    for (int i = 1; i <= c1; ++i)
      for (int j = 1; j <= c2; ++j)
        pushToQueue(moves1[i].x, moves1[i].y, moves2[i].x, moves2[i].y, t->moves + 1);
    pop();
  }
  return -1;
}
void program() {
  int tcase, moves;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d %d %d %d %d", &figure1.type, &figure1.x, &figure1.y, &figure2.type, &figure2.x, &figure2.y);
    pushToQueue(figure1.x, figure1.y, figure2.x, figure2.y, 0);
    moves = bfs();
    if (moves != -1) printf("%d\n", moves);
    else printf("INF\n");
  }
}
int main() {
  program();
  return 0;
}
// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
#define M_MAX 1000
#define INF 1e9
#define DIR_MAX 4
using namespace std;
typedef long long int ll;
char input[BUFF(N_MAX)][BUFF(M_MAX)];
ll dist[BUFF(N_MAX)][BUFF(M_MAX)];
int n, m, sx, sy;
bool isPossible(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= m || input[x][y] == '#') return false;
  return true;
}
ll costs[BUFF(DIR_MAX)];
int move_x[] = {  0, 0, -1, 1 };
int move_y[] = { -1, 1,  0, 0 };
ll distances[BUFF(N_MAX * M_MAX)];
int d_ptr;
struct Q {
  int x, y;
  ll dist;
} t_queue[BUFF(N_MAX * M_MAX)];
int front, rear;
void offset(int &x) {
  if (x == (N_MAX * M_MAX)) x = 0;
}
void push(int x, int y, ll dist) {
  t_queue[rear].x = x;
  t_queue[rear].y = y;
  t_queue[rear].dist = dist;
  ++rear;
  offset(rear);
}
void pop() {
  ++front;
  offset(front);
}
bool isEmpty() { return front == rear; }
void bfs() {
  struct Q *t;
  int next_x, next_y;
  push(sx, sy, 0);
  dist[sx][sy] = 0;
  while (!isEmpty()) {
    t = &t_queue[front];
    pop();
    for (int i = 0; i < DIR_MAX; ++i) {
      next_x = t->x + move_x[i];
      next_y = t->y + move_y[i];
      if (isPossible(next_x, next_y) && dist[next_x][next_y] > (t->dist + costs[i])) {
        push(next_x, next_y, t->dist + costs[i]);
        dist[next_x][next_y] = t->dist + costs[i];
      }
    }
  }
}
void pushDistance(ll val) {
  distances[d_ptr++] = val;
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int findBS(ll x) {
  int l, r, mid;
  l = 0;
  r = d_ptr - 1;
  while (l <= r) {
    mid = getMid(l, r);
    if (distances[mid] <= x)
      l = mid + 1;
    else r = mid - 1;
  }
  return l - 1;
}
void program() {
  ll t_dist;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf(" %s", input[i]);
    for (int j = 0; j < m; ++j)
      dist[i][j] = INF;
  }
  for (int i = 0; i < DIR_MAX; ++i)
    scanf("%lld", &costs[i]);
  scanf("%d %d", &sx, &sy);
  --sx, --sy;
  bfs();
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (input[i][j] == '.')
        pushDistance(dist[i][j]);
  sort(distances, distances + d_ptr);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &t_dist);
    printf("%d\n", findBS(t_dist) + 1);
  }
}
int main() {
  program();
  return 0;
}
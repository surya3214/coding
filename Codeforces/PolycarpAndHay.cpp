// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m;
ll k;
struct {
  int root, size;
} groups[BUFF(N_MAX * N_MAX)];
struct {
  int val, g_id, visited;
} graph[BUFF(N_MAX)][BUFF(N_MAX)];
struct P {
  P() {}
  P(int t_x, int t_y) : x(t_x), y(t_y) {}
  bool operator <(P r) { return graph[x][y].val > graph[r.x][r.y].val; }
  int x, y;
};
vector<P> s_points;
int move_x[] = { -1, 1, 0, -1 };
int move_y[] = {  0, 0, 1,  0 };
struct {
  int val;
  int graph[BUFF(N_MAX)][BUFF(N_MAX)];
} ans;
bool isPossible(P p) {
  if (p.x >= 1 && p.x <= n && p.y >= 1 && p.y <= m && graph[p.x][p.y].visited)
    return true;
  return false;
}
int getGroupRoot(int g_id) {
  if (groups[g_id].root != g_id)
    groups[g_id].root = getGroupRoot(groups[g_id].root);
  return groups[g_id].root;
}
void groupify(P a, P b) {
  int a_grp, b_grp;
  a_grp = getGroupRoot(graph[a.x][a.y].g_id);
  b_grp = getGroupRoot(graph[b.x][b.y].g_id);
  if (a_grp != b_grp) {
    groups[a_grp].size += groups[b_grp].size;
    graph[b.x][b.y].g_id = graph[a.x][a.y].g_id = a_grp;
  }
}
void pickReqFrom(P p, int req) {
  queue<P> q;
  int picked = 0, g_id, next_g_id;
  P cur, next;
  for (q.push(p), g_id = getGroupRoot(graph[p.x][p.y].g_id); !q.empty() && picked != req; q.pop()) {
    cur = q.front();
    ans.graph[cur.x][cur.y] = ans.val;
    ++picked;
    for (int i = 0; i < 4; ++i) {
      next.x = cur.x + move_x[i];
      next.y = cur.y + move_y[i];
      if (isPossible(next)) {
        next_g_id = getGroupRoot(graph[next.x][next.y].g_id);
        if (next_g_id == g_id)
          q.push(next);
      }
    }
  }
}
void process() {
  P next;
  int required, root;
  sort(s_points.begin(), s_points.end());
  for (auto cur: s_points) {
    graph[cur.x][cur.y].visited = true;
    for (int i = 0; i < 4; ++i) {
      next.x = cur.x + move_x[i];
      next.y = cur.y + move_y[i];
      if (isPossible(next)) {
        groupify(cur, next);
        root = getGroupRoot(graph[cur.x][cur.y].g_id);
        printf("", groups[root].size);
      }
    }
    if (!(k % graph[cur.x][cur.y].val)) {
      required = k / graph[cur.x][cur.y].val;
      root = getGroupRoot(graph[cur.x][cur.y].g_id);
      if (groups[root].size >= required) {
        ans.val = graph[cur.x][cur.y].val;
        pickReqFrom(cur, required);
        return;
      }
    }
  }
}
void program() {
  scanf("%d %d %lld", &n, &m, &k);
  for (int i = 1, g_id = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j, ++g_id) {
      scanf("%d", &graph[i][j].val);
      graph[i][j].g_id = g_id;
      groups[g_id].root = g_id;
      groups[g_id].size = 1;
      s_points.push_back({ i, j });
    }
  }
  process();
  if (ans.val) {
    printf("YES\n");
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j)
        printf("%d ", ans.graph[i][j]);
      printf("\n");
    }
  } else printf("NO\n");
}
int main() {
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}
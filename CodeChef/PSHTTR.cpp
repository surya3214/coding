// AC DFS, BIT
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define M_MAX (int) 1e5
#define E_MAX (N_MAX + M_MAX)
#define B_MAX (2 * E_MAX)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
struct {
  int depth, start, end;
  vector<int> adj;
} castles[BUFF(N_MAX)];
int t_time;
struct E {
  int u, v, k, pos;
  bool type;
  E() {}
  E(int u, int v, int k, int pos = 0, bool type = false) : u(u), v(v), k(k), pos(pos), type(type) {}
  bool operator <(E b) {
    if (k == b.k && type != b.type)
      return !type;
    return k < b.k;
  }
} events[BUFF(E_MAX)];
int ans[BUFF(M_MAX)];
int e_ptr;
struct {
  int time;
  int val;
} BIT[BUFF(B_MAX)];
int b_time;
void reset() {
  e_ptr = t_time = 0;
  ++b_time;
  for (int i = 1; i <= N_MAX; ++i)
    castles[i].adj.clear();
}
void dfs(int cur, int prev) {
  castles[cur].depth = castles[prev].depth + 1;
  castles[cur].start = ++t_time;
  for (auto next: castles[cur].adj)
    if (next != prev)
      dfs(next, cur);
  castles[cur].end = ++t_time;
}
void process() {
  dfs(1, 0);
  sort(events + 1, events + 1 + e_ptr);
}
void sanitizeBIT(int idx) {
  if (BIT[idx].time != b_time) {
    BIT[idx].time = b_time;
    BIT[idx].val = 0;
  }
}
void addToBIT(int val, int idx) {
  while (idx <= t_time) {
    sanitizeBIT(idx);
    BIT[idx].val ^= val;
    idx += (idx & -idx);
  }
}
int queryBIT(int idx) {
  int ret = 0;
  while (idx) {
    sanitizeBIT(idx);
    ret ^= BIT[idx].val;
    idx -= (idx & -idx);
  }
  return ret;
}
void addEdge(int e_idx) {
  int u, v;
  u = events[e_idx].u, v = events[e_idx].v;
  if (castles[v].depth < castles[u].depth)
    swap(u, v);
  addToBIT(events[e_idx].k, castles[v].start);
  addToBIT(events[e_idx].k, castles[v].end + 1);
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1, u, v, k, m; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
      scanf("%d %d %d", &u, &v, &k);
      castles[u].adj.push_back(v);
      castles[v].adj.push_back(u);
      events[++e_ptr] = E(u, v, k);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
      scanf("%d %d %d", &u, &v, &k);
      events[++e_ptr] = E(u, v, k, i, true);
    }
    process();
    for (int i = 1; i <= e_ptr; ++i) {
      if (events[i].type) {
        ans[events[i].pos] = queryBIT(castles[events[i].u].start);
        ans[events[i].pos] ^= queryBIT(castles[events[i].v].start);
      } else addEdge(i);
    }
    for (int i = 1; i <= m; ++i)
      printf("%d\n", ans[i]);
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
// TLE - have to find followers in cycles
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 9999
#define M_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n, q;
int t_time;
struct L {
  int v;
  struct L *next;
} l_nodes_pool[BUFF(M_MAX)];
int l_ptr;
struct {
  int us[BUFF(N_MAX)];
  int max_cnt;
  int max_ptr;
} max_followers;
struct {
  int time;
  struct L *q;
} nodes[BUFF(N_MAX)];
void reset() { ++t_time; l_ptr = max_followers.max_cnt = max_followers.max_ptr = 0; }
void sanitizeNode(int u) {
  if (nodes[u].time != t_time) {
    nodes[u].q = NULL;
    nodes[u].time = t_time;
  }
}
struct L *getLNodesFromPool() { return &l_nodes_pool[l_ptr++]; }
void addToMaxFollowers(int u) {
  int pos = ++max_followers.max_ptr;
  max_followers.us[pos] = u;
}
void compareWithMax(int r, int u) {
  if (max_followers.max_cnt > r) return;
  if (r > max_followers.max_cnt) {
    max_followers.max_cnt = r;
    max_followers.max_ptr = 0;
  }
  addToMaxFollowers(u);
}
void addFollowers(int u, int v) {
  sanitizeNode(u);
  struct L *t = getLNodesFromPool();
  t->v = v;
  t->next = nodes[u].q;
  nodes[u].q = t;
}
bool visited[BUFF(N_MAX)];
int compute(int u) {
  if (visited[u]) return 0;
  sanitizeNode(u);
  visited[u] = true;
  struct L *t = nodes[u].q;
  int ret = 1;
  while (t) {
    ret += compute(t->v);
    t = t->next;
  }
  visited[u] = false;
  return ret;
}
void program() {
  int tcase, a, b;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= q; ++i) {
      scanf("%d %d", &a, &b);
      addFollowers(b, a);
    }
    for (int i = 1; i <= N_MAX; ++i)
      compareWithMax(compute(i), i);
    sort(max_followers.us + 1, max_followers.us + 1 + max_followers.max_ptr);
    for (int i = 1; i <= max_followers.max_ptr; ++i)
      printf("%d ", max_followers.us[i]);
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}
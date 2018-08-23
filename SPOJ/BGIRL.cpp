// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define M_MAX 100000
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
bool isComposite[BUFF(N_MAX)];
int n, q, t_time, ans;
struct L {
  int v;
  struct L *next;
} l_nodes_pool[BUFF(M_MAX * 2)];
int l_pool_ptr;
struct {
  int time;
  bool visited;
  struct L *children;
} nodes[BUFF(N_MAX)];
void reset() { ++t_time; ans = -1; l_pool_ptr = 0; }
void preprocess() {
  isComposite[1] = true;
  for (int i = 3; i <= N_MAX; i += 2) {
    if (!isComposite[i]) { // a prime number
      for (int j = i + i; j <= N_MAX; j += i)
        isComposite[j] = true;
    }
  }
}
void sanitizeNode(int u) {
  if (nodes[u].time != t_time) {
    nodes[u].visited = false;
    nodes[u].children = NULL;
    nodes[u].time = t_time;
  }
}
struct L *getLNodesFromPool() { return &l_nodes_pool[l_pool_ptr++]; }
void addChildren(int u, int v) {
  sanitizeNode(u);
  sanitizeNode(v);
  struct L *t = getLNodesFromPool();
  t->v = v;
  t->next = nodes[u].children;
  nodes[u].children = t;
}
int dfs(int u) {
  int ret = 1;
  nodes[u].visited = true;
  struct L *t = nodes[u].children;
  while (t) {
    if (!nodes[t->v].visited)
      ret += dfs(t->v);
    t = t->next;
  }
  return ret;
}
void program() {
  int tcase, u, v, ret;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= q; ++i) {
      scanf("%d %d", &u, &v);
      addChildren(u, v);
      addChildren(v, u);
    }
    for (int i = 1; i <= n; ++i) {
      sanitizeNode(i);
      if (!nodes[i].visited) {
        ret = dfs(i);
        if (ret == 2 || ret & 1 && !isComposite[ret]) // ret is 2 or odd and prime
          ans = max(ans, ret);
      }
    }
    printf("%d\n", ans);
  }
}
int main() {
  preprocess();
  program();
  return 0;
}
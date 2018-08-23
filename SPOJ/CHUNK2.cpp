// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX 1300000
#define N_MAX 100000
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
bool isComposite[BUFF(VAL_MAX)];
int primes[BUFF(N_MAX)];
int t_time, ans;
struct L {
  int v;
  struct L *next;
} l_nodes_pool[BUFF(N_MAX * 2)];
int l_pool_ptr;
void reset() { ++t_time; l_pool_ptr = ans = 0; }
struct {
  int time;
  bool visited;
  struct L *children;
} nodes[BUFF(N_MAX)];
void addToPrimes(int x) { int pos = ++primes[0]; primes[pos] = x; }
void preprocess() {
  addToPrimes(2);
  int i = 3;
  while (primes[0] <= N_MAX) {
    if (!isComposite[i]) { // is a prime number
      addToPrimes(i);
      for (int j = i + i; j < VAL_MAX; j += i)
        isComposite[j] = true;
    }
    i += 2;
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
  int tcase, n, q, u, v;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d", &n, &q);
    if (!q) printf("-1\n");
    else {
      for (int i = 1; i <= q; ++i) {
        scanf("%d %d", &u, &v);
        addChildren(u, v);
        addChildren(v, u);
      }
      for (int i = 1; i <= n; ++i) {
        sanitizeNode(i);
        if (!nodes[i].visited)
          ans = max(ans, dfs(i));
      }
      printf("%d\n", primes[ans]);
    }
  }
}
int main() {
  preprocess();
  program();
  return 0;
}
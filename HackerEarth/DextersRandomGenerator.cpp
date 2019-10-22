// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (1e5)
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#define BITS_MAX 30
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
struct {
  int val;
  vector<int> adj;
} vertices[BUFF(N_MAX)];
struct N {
  int l, r, cnt;
} nodes[BUFF(NODES_MAX)];
int nodes_ptr, t_roots[BUFF(N_MAX)];
int dfs(int prev, int u) {
  int cur, ret;
  cur = ret = ++nodes_ptr;
  nodes[cur] = nodes[prev];

  return ret;
}
void process() {
  t_roots[1] = dfs(t_roots[0], 1);
}
void program() {
  int q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &vertices[i].val);
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d %d", &u, &v);
    vertices[u].adj.push_back(v);
    vertices[v].adj.push_back(u);
  }
  process();
  for (int i = 1, u, v; i <= q; ++i) {
    scanf("%d %d", &u, &v);
    printf("%d\n", solve(u, v));
  }
}
int main() {
#ifndef ONLINE_JUDGE
  // freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
// AC Graph Theory Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct {
  int size, h;
  vector<int> edges;
  bool visited;
} nodes[BUFF(N_MAX)];
struct E {
  E() {}
  E(int t_u, int t_v) : u(t_u), v(t_v) {}
  int u, v;
} edges[BUFF(N_MAX)];
int e_ptr;
static void addToEdges(int u, int v) { edges[++e_ptr] = {u, v}; }
static void dfs(int u, int h) {
  nodes[u].visited = true;
  nodes[u].h = h;
  ++nodes[u].size;
  int v;
  for (int i = 0; i < nodes[u].edges.size(); ++i) {
    v = edges[nodes[u].edges[i]].u == u ? edges[nodes[u].edges[i]].v : edges[nodes[u].edges[i]].u;
    if (!nodes[v].visited) {
      dfs(v, h + 1);
      nodes[u].size += nodes[v].size;
    }
  }
}
void program() {
  int q, u, v;
  scanf("%d %d", &n, &q);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d", &u, &v);
    addToEdges(u, v);
    nodes[u].edges.push_back(e_ptr);
    nodes[v].edges.push_back(e_ptr);
  }
  dfs(1, 1);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &u);
    if (nodes[edges[u].u].h < nodes[edges[u].v].h)
      v = edges[u].v;
    else v = edges[u].u;
    printf("%lld\n", 1LL * nodes[v].size * (n - nodes[v].size));
  }
}
int main() {
  program();
  return 0;
}
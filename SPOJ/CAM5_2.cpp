// AC DFS
#include <bits/stdc++.h>
#define N_MAX 100010
#define E_MAX (N_MAX / 2) * 2
using namespace std;
int start[N_MAX];
bool visited[N_MAX];
struct E {
  int v, next;
} edges[E_MAX];
int n, e, ans;
void reset() {
  ans = 0;
  for (int i = 0; i < n; i++)
    start[i] = -1, visited[i] = false;
}
void dfs(int u) {
  if (visited[u])
    return;
  visited[u] = true;
  int t = start[u], v;
  while (t != -1) {
    v = edges[t].v;
    if (!visited[v])
      dfs(v);
    t = edges[t].next;
  }
}
void program() {
  int t, u, v, edge_ptr;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d", &n, &e);
    reset();
    edge_ptr = 0;
    for (int i = 1; i <= e; i++) {
      scanf("%d %d", &u, &v);
      edges[edge_ptr].v = v;
      edges[edge_ptr].next = start[u];
      start[u] = edge_ptr;
      edge_ptr++;
      edges[edge_ptr].v = u;
      edges[edge_ptr].next = start[v];
      start[v] = edge_ptr;
      edge_ptr++;
    }
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        ans++;
        dfs(i);
      }
    }
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
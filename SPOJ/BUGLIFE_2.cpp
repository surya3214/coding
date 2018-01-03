// AC DFS
#include <bits/stdc++.h>
#define N_MAX 2010
#define E_MAX 1000010 * 2
using namespace std;
int n, e;
bool visited[N_MAX], valid;
int group[N_MAX], start[N_MAX], edge_ptr;
struct E {
  int v, next;
} edges[E_MAX];
int col[] = {1, 2};
void reset() {
  edge_ptr = 0;
  valid = true;
  for (int i = 0; i <= n; i++)
    group[i] = visited[i] = 0, start[i] = -1;
}
void addEdge(int u, int v) {
  edges[edge_ptr].v = v;
  edges[edge_ptr].next = start[u];
  start[u] = edge_ptr;
  edge_ptr++;
}
void dfs(int u, bool idx) {
  if (group[u] == 0)
    group[u] = col[idx];
  else if (group[u] != col[idx])
    valid = false;
  if (visited[u] || !valid)
    return;
  visited[u] = true;
  int t = start[u], v;
  while (t != -1) {
    v = edges[t].v;
    dfs(v, !idx);
    t = edges[t].next;
  }
}
void program() {
  int tcase, u, v;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; t++) {
    scanf("%d %d", &n, &e);
    reset();
    for (int i = 0; i < e; i++) {
      scanf("%d %d", &u, &v);
      addEdge(u, v);
      addEdge(v, u);
    }
    for (int i = 1; i <= n && valid; i++)
      if (!visited[i])
        dfs(i, 0);
    printf("Scenario #%d:\n", t);
    if (valid)
      printf("No suspicious bugs found!\n");
    else printf("Suspicious bugs found!\n");
  }
}
int main() {
  program();
  return 0;
}
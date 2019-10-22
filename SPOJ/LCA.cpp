// AC LCA, Tree
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e3
#define H_MAX 10
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
struct {
  bool child;
  int depth;
  int parent[BUFF(H_MAX)];
  vector<int> adj;
} vertices[BUFF(N_MAX)];
void reset() {
  for (int i = 1; i <= n; ++i) {
    vertices[i].child = false;
    vertices[i].adj.clear();
  }
}
void dfs(int cur, int prev) {
  vertices[cur].depth = vertices[prev].depth + 1;
  vertices[cur].parent[0] = prev;
  for (int i = 1; i <= H_MAX && vertices[cur].parent[i - 1]; ++i)
    vertices[cur].parent[i] = vertices[vertices[cur].parent[i - 1]].parent[i - 1];
  for (auto next: vertices[cur].adj) {
    if (next != prev)
      dfs(next, cur);
  }
}
void process() {
  for (int u = 1; u <= n; ++u) {
    if (!vertices[u].child) { // root
      dfs(u, 0);
      break;
    }
  }
}
int LCA(int u, int v) {
  if (vertices[u].depth < vertices[v].depth)
    swap(u, v);
  // bring them to same depth
  int diff = vertices[u].depth - vertices[v].depth;
  for (int i = H_MAX, val = 1 << H_MAX; i >= 0 && diff; --i, val = val >> 1) {
    if (diff >= val) {
      u = vertices[u].parent[i];
      diff -= val;
    }
  }
  if (u == v)
    return u;
  for (int i = H_MAX; i >= 0; --i) {
    if (vertices[u].parent[i] != vertices[v].parent[i]) {
      u = vertices[u].parent[i];
      v = vertices[v].parent[i];
    }
  }
  return vertices[u].parent[0];
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1, q; t <= tcase; ++t) {
    scanf("%d", &n);
    reset();
    for (int u = 1, x, v; u <= n; ++u) {
      scanf("%d", &x);
      for (int j = 1; j <= x; ++j) {
        scanf("%d", &v);
        vertices[u].adj.push_back(v);
        vertices[v].child = true;
      }
    }
    process();
    printf("Case %d:\n", t);
    scanf("%d", &q);
    for (int i = 1, u, v; i <= q; ++i) {
      scanf("%d %d", &u, &v);
      printf("%d\n", LCA(u, v));
    }
  }
}
int main() {
#ifndef ONLINE_JUDGE
  // freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
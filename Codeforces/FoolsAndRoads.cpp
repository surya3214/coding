// AC LCA Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define H_MAX 17
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n, ans[BUFF(N_MAX)];
struct {
  int reps, sum, depth;
  int parent[BUFF(H_MAX)];
  vector<pii> edges;
} vertices[BUFF(N_MAX)];
void dfs(int cur, int prev, int edge_id) {
  vertices[cur].parent[0] = prev;
  for (int i = 1, x; i <= H_MAX; ++i) {
    x = vertices[cur].parent[i - 1];
    vertices[cur].parent[i] = x ? vertices[x].parent[i - 1] : 0;
  }
  vertices[cur].depth = vertices[prev].depth + 1;
  vertices[cur].reps = edge_id;
  for (auto next: vertices[cur].edges)
    if (next.first != prev)
      dfs(next.first, cur, next.second);
}
int findLCA(int u, int v) {
  if (vertices[u].depth < vertices[v].depth)
    swap(u, v);
  int diff = vertices[u].depth - vertices[v].depth;
  for (int i = H_MAX, cur_rep = (1 << H_MAX); i >= 0 && diff; --i, cur_rep >>= 1) {
    if (diff >= cur_rep) {
      u = vertices[u].parent[i];
      diff -= cur_rep;
    }
  }
  if (u != v) {
    for (int i = H_MAX, cur_rep = (1 << H_MAX); i >= 0; --i, cur_rep >>= 1) {
      if (vertices[u].parent[i] != vertices[v].parent[i]) {
        u = vertices[u].parent[i];
        v = vertices[v].parent[i];
      }
    }
    u = vertices[u].parent[0];
  }
  return u;
}
void computeAns(int cur, int prev) {
  int sum = 0;
  for (auto next: vertices[cur].edges) {
    if (next.first != prev) {
      computeAns(next.first, cur);
      sum += ans[vertices[next.first].reps];
    }
  }
  sum += vertices[cur].sum;
  ans[vertices[cur].reps] = sum;
}
void program() {
  scanf("%d", &n);
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d %d", &u, &v);
    vertices[u].edges.push_back({ v, i });
    vertices[v].edges.push_back({ u, i });
  }
  dfs(1, 0, 0);
  int q;
  scanf("%d", &q);
  for (int i = 1, u, v, lca; i <= q; ++i) {
    scanf("%d %d", &u, &v);
    ++vertices[u].sum;
    ++vertices[v].sum;
    lca = findLCA(u, v);
    vertices[lca].sum -= 2;
  }
  computeAns(1, 0);
  for (int i = 1; i < n; ++i)
    printf("%d ", ans[i]);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
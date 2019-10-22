// AC LCA, Tree, Binary lifting
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
int n;
struct E {
  int u, v, val;
} edges[BUFF(N_MAX)];
int e_ptr;
struct {
  int depth;
  struct {
    int min, max, v;
  } parent[BUFF(H_MAX)];
  vector<int> adj;
} vertices[BUFF(N_MAX)];
void dfs(int cur, int prev, int val) {
  vertices[cur].depth = vertices[prev].depth + 1;
  vertices[cur].parent[0].min = vertices[cur].parent[0].max = val;
  vertices[cur].parent[0].v = prev;
  for (int i = 1, half; i <= H_MAX && vertices[cur].parent[i - 1].v; ++i) {
    half = vertices[cur].parent[i - 1].v;
    vertices[cur].parent[i].min = min(vertices[cur].parent[i - 1].min, vertices[half].parent[i - 1].min);
    vertices[cur].parent[i].max = max(vertices[cur].parent[i - 1].max, vertices[half].parent[i - 1].max);
    vertices[cur].parent[i].v = vertices[half].parent[i - 1].v;
  }
  int next;
  for (auto e_idx: vertices[cur].adj) {
    next = (edges[e_idx].u != cur) ? edges[e_idx].u : edges[e_idx].v;
    if (next != prev)
      dfs(next, cur, edges[e_idx].val);
  }
}
void process() {
  dfs(1, 0, 0);
}
void LCA(int u, int v, int &a, int &b) {
  a = INT_MAX;
  b = INT_MIN;
  if (vertices[u].depth < vertices[v].depth)
    swap(u, v);
  int diff = vertices[u].depth - vertices[v].depth;
  for (int i = H_MAX, val = (1 << H_MAX); i >= 0 && diff; --i, val >>= 1) {
    if (diff >= val) {
      a = min(a, vertices[u].parent[i].min);
      b = max(b, vertices[u].parent[i].max);
      u = vertices[u].parent[i].v;
      diff -= val;
    }
  }
  if (u == v)
    return;
  for (int i = H_MAX; i >= 0; --i) {
    if (vertices[u].parent[i].v != vertices[v].parent[i].v) {
      a = min(a, vertices[u].parent[i].min);
      b = max(b, vertices[u].parent[i].max);
      u = vertices[u].parent[i].v;
      a = min(a, vertices[v].parent[i].min);
      b = max(b, vertices[v].parent[i].max);
      v = vertices[v].parent[i].v;
    }
  }
  a = min(a, vertices[u].parent[0].min);
  b = max(b, vertices[u].parent[0].max);
  a = min(a, vertices[v].parent[0].min);
  b = max(b, vertices[v].parent[0].max);
}
void program() {
  int u, v, k;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d %d", &u, &v, &k);
    edges[++e_ptr] = { u, v, k };
    vertices[u].adj.push_back(e_ptr);
    vertices[v].adj.push_back(e_ptr);
  }
  process();
  scanf("%d", &k);
  for (int a, b; k; --k) {
    scanf("%d %d", &u, &v);
    LCA(u, v, a, b);
    printf("%d %d\n", a, b);
  }
}
int main() {
#ifndef ONLINE_JUDGE
  // freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
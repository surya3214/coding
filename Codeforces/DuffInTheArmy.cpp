// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#define H_MAX 17
#define A_MAX 10
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n, m;
struct {
  int root, depth;
  int parent[BUFF(H_MAX)];
  vector<int> edges, people;
} vertices[BUFF(N_MAX)];
struct N {
  N() {}
  N(int l, int r, int cnt) : l(l), r(r), cnt(cnt) {}
  int l, r, left_most;
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int ans[BUFF(A_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int pos, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    nodes[cur] = nodes[prev];
    if (l == r)
      ++nodes[cur].cnt;
    else {
      int mid = getMid(l, r);
      int a = buildTree(nodes[prev].l, pos, l, mid);
      int b = buildTree(nodes[prev].r, pos, mid + 1, r);
      int c = nodes[a].left_most ? nodes[a].left_most : nodes[b].left_most;
      nodes[cur] = N(a, b, c);
    }
    return cur;
  }
  return prev;
}
void dfs(int cur, int prev) {
  vertices[cur].depth = vertices[prev].depth + 1;
  vertices[cur].parent[0] = prev;
  for (int i = 1, x; i <= H_MAX; ++i) {
    x = vertices[cur].parent[i - 1];
    vertices[cur].parent[i] = x ? vertices[x].parent[i - 1] : 0;
  }
  vertices[cur].root = ++nodes_ptr;
  nodes[vertices[cur].root] = nodes[vertices[prev].root];
  for (auto p: vertices[cur].people)
    vertices[cur].root = buildTree(vertices[cur].root, p, 1, m);
  for (auto next: vertices[cur].edges)
    if (next != prev)
      dfs(next, cur);
}
void resetAns() { ans[0] = 0; }
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
    for (int i = H_MAX; i >= 0; --i) {
      if (vertices[u].parent[i] != vertices[v].parent[i]) {
        u = vertices[u].parent[i];
        v = vertices[v].parent[i];
      }
    }
    u = vertices[u].parent[0];
  }
  return u;
}
int queryAns(int a, int b, int c, int d, int t_l, int t_r, int l, int r) {
  int cnt = nodes[a].cnt - nodes[d].cnt + nodes[b].cnt - nodes[c].cnt;
  if (!cnt)
    return m + 1;
  if (l == r) {
    return l;
  } else if (t_l <=l && r <= t_r) {
    int mid = getMid(l, r);
    cnt = queryAns(nodes[a].l, nodes[b].l, nodes[c].l, nodes[d].l);
    if (cnt <= m)
      return cnt;
    cnt = queryAns(nodes[a].r, nodes[b].r, nodes[c].r, nodes[d].r);
    if (cnt <= m)
      return cnt;
  }
  return m + 1;
}
void findAns(int u, int v, int a) {
  int lca, p_lca;
  lca = findLCA(u, v);
  p_lca = vertices[lca].parent[0];
  int last = 0;
  do {
    last = queryAns(vertices[u].root, vertices[v].root, vertices[lca].root, vertices[p_lca].root, last + 1, m, 1, m);
    if (last <= m)
      ans[++ans[0]] = last;
    --a;
  } while (last < m && a);
}
void program() {
  int q;
  scanf("%d %d %d", &n, &m, &q);
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d %d", &u, &v);
    vertices[u].edges.push_back(v);
    vertices[v].edges.push_back(u);
  }
  for (int i = 1, u; i <= m; ++i) {
    scanf("%d", &u);
    vertices[u].people.push_back(i);
  }
  dfs(1, 0);
  for (int i = 1, u, v, a; i <= q; ++i) {
    resetAns();
    scanf("%d %d %d", &u, &v, &a);
    findAns(u, v, a);
    for (int j = 0; j <= ans[0]; ++j)
      printf("%d ", ans[j]);
    printf("\n");
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
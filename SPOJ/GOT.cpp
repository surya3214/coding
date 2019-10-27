// AC Persistent Segment Tree
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#define H_MAX 17
// #pragma GCC optimize "O0"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
int powers[BUFF(H_MAX)];
struct {
  int val, tree_pos, depth;
  vector<int> edges;
  int p[BUFF(H_MAX)];
} vertices[BUFF(N_MAX)];
struct V {
  V() {}
  V(int val, int idx) : val(val), idx(idx) {}
  bool operator <(V other) { return val < other.val; }
  int val, idx;
} values[BUFF(N_MAX)];
struct N {
  N() {}
  N(int l, int r, int cnt) : l(l), r(r), cnt(cnt) {}
  int l, r, cnt;
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(N_MAX)];
void calculateTreePos() {
  sort(values + 1, values + 1 + n);
  values[0] = V(-1, -1);
  for (int i = 1, cur = 0; i <= n; ++i) {
    if (values[i].val != values[i - 1].val)
      ++cur;
    vertices[values[i].idx].tree_pos = cur;
  }
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int pos, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    if (l == r) {
      nodes[cur] = nodes[prev];
      ++nodes[cur].cnt;
    } else {
      int mid = getMid(l, r);
      int a = buildTree(nodes[prev].l, pos, l, mid);
      int b = buildTree(nodes[prev].r, pos, mid + 1, r);
      nodes[cur] = N(a, b, nodes[a].cnt + nodes[b].cnt);
    }
    return cur;
  }
  return prev;
}
void dfs(int u, int p) {
  vertices[u].p[0] = p;
  for (int i = 1, x; i <= H_MAX; ++i) {
    x = vertices[u].p[i - 1];
    vertices[u].p[i] = x ? vertices[x].p[i - 1] : 0;
  }
  vertices[u].depth = vertices[p].depth + 1;
  roots[u] = buildTree(roots[p], vertices[u].tree_pos, 1, n);
  for (auto v: vertices[u].edges)
    if (v != p)
      dfs(v, u);
}
void reset() { nodes_ptr = 0; }
bool isPresent(int x, int &pos) {
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (values[mid].val == x) {
      pos = vertices[values[mid].idx].tree_pos;
      return true;
    } else if (x < values[mid].val)
      r = mid - 1;
    else l = mid + 1;
  }
  return false;
}
int getLCA(int u, int v) {
  if (vertices[u].depth < vertices[v].depth)
    swap(u, v);
  int diff = vertices[u].depth - vertices[v].depth;
  for (int i = H_MAX, cur_h; i >= 0 && diff; --i) {
    cur_h = powers[i];
    if (cur_h <= diff) {
      u = vertices[u].p[i];
      diff -= cur_h;
    }
  }
  if (u == v)
    return v;
  for (int i = H_MAX; i >= 0; --i) {
    if (vertices[u].p[i] != vertices[v].p[i]) {
      u = vertices[u].p[i];
      v = vertices[v].p[i];
    }
  }
  return vertices[u].p[0];
}
int queryCount(int cur, int pos, int l, int r) {
  if (!cur || !nodes[cur].cnt)
    return 0;
  else if (l == r)
    return nodes[cur].cnt;
  int mid = getMid(l, r);
  return (pos <= mid) ?
    queryCount(nodes[cur].l, pos, l, mid) :
    queryCount(nodes[cur].r, pos, mid + 1, r);
}
bool isFound(int u, int v, int w) {
  int pos;
  if (!isPresent(w, pos))
    return false;
  int lca = getLCA(u, v);
  int p = vertices[lca].p[0];
  int ret = queryCount(roots[u], pos, 1, n) - queryCount(roots[p], pos, 1, n) +
            queryCount(roots[v], pos, 1, n) - queryCount(roots[lca], pos, 1, n);
  return ret;
}
void program() {
  int m;
  while (scanf("%d %d", &n, &m) != EOF) {
    reset();
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &vertices[i].val);
      values[i] = V(vertices[i].val, i);
      vertices[i].edges.clear();
    }
    for (int i = 1, u, v; i < n; ++i) {
      scanf("%d %d", &u, &v);
      vertices[u].edges.push_back(v);
      vertices[v].edges.push_back(u);
    }
    calculateTreePos();
    dfs(1, 0);
    for (int i = 1, u, v, w; i <= m; ++i) {
      scanf("%d %d %d", &u, &v, &w);
      if (isFound(u, v, w))
        printf("Find\n");
      else printf("NotFind\n");
    }
    printf("\n");
  }
}
void ready() {
  powers[0] = 1;
  for (int i = 1; i <= H_MAX; ++i)
    powers[i] = powers[i - 1] << 1;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  ready();
  program();
  return 0;
}
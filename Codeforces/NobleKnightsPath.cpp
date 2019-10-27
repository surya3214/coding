// AC Persistent Segment Tree, Linearization, HARD
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define EVENTS_MAX (int) 1e5
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#define H_MAX 17
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
struct {
  int depth, inTime, outTime, parent[BUFF(H_MAX)];
  vector<int> edges;
} vertices[BUFF(N_MAX)];
int root;
struct N {
  N() {}
  N(int l, int r, int cnt) : l(l), r(r), cnt(cnt) {}
  int l, r, cnt;
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int linearized_vs[BUFF(2 * N_MAX)]; // PST is built on this
int t_time;
int events[BUFF(EVENTS_MAX)];
void dfs(int cur, int prev) {
  vertices[cur].inTime = ++t_time;
  vertices[cur].depth = vertices[prev].depth + 1;
  vertices[cur].parent[0] = prev;
  for (int i = 1, x; i <= H_MAX; ++i) {
    x = vertices[cur].parent[i - 1];
    vertices[cur].parent[i] = x ? vertices[x].parent[i - 1] : 0;
  }
  for (auto next: vertices[cur].edges)
    dfs(next, cur);
  vertices[cur].outTime = ++t_time;
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int pos, int val, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    if (l == r)
      nodes[cur].cnt = val;
    else {
      int mid = getMid(l, r);
      int a = buildTree(nodes[prev].l, pos, val, l, mid);
      int b = buildTree(nodes[prev].r, pos, val, mid + 1, r);
      nodes[cur] = N(a, b, nodes[a].cnt + nodes[b].cnt);
    }
    return cur;
  }
  return prev;
}
int findLCA(int u, int v) {
  if (vertices[u].depth < vertices[v].depth)
    swap(u, v);
  int diff = vertices[u].depth - vertices[v].depth;
  for (int i = H_MAX, cur_rep = (1 << H_MAX); i >= 0; --i, cur_rep >>= 1) {
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
int queryCount(int a, int b, int t_l, int t_r, int l, int r) {
  if (!a || t_r < l || r < t_l)
    return 0;
  else if (t_l <=l && r <= t_r)
    return nodes[a].cnt - nodes[b].cnt;
  else {
    int mid = getMid(l, r);
    int x = queryCount(nodes[a].l, nodes[b].l, t_l, t_r, l, mid);
    int y = queryCount(nodes[a].r, nodes[b].r, t_l, t_r, mid + 1, r);
    return x + y;
  }
}
int getGoodNodes(int a, int b, int u, int v) {
  int total = vertices[u].depth - vertices[v].depth + 1;
  return total - queryCount(a, b, vertices[v].inTime, vertices[u].inTime, 1, (2 * n));
}
int getKthGoodNode(int a, int b, int u, int v, int k) {
  for (int i = H_MAX, x, y; i >= 0; --i) {
    x = vertices[u].parent[i];
    if (x && vertices[v].depth <= vertices[x].depth) {
      y = getGoodNodes(a, b, u, x);
      if (y < k) {
        k -= y;
        u = x;
        k += getGoodNodes(a, b, u, u);
      }
    }
  }
  return (k == 1 && getGoodNodes(a, b, u, u)) ? u : vertices[u].parent[0];
}
void program() {
  scanf("%d", &n);
  for (int i = 1, x; i <= n; ++i) {
    scanf("%d", &x);
    if (x)
      vertices[x].edges.push_back(i);
    else root = i;
  }
  dfs(root, 0);
  int q;
  scanf("%d", &q);
  for (int i = 1, type, u, v, k, y, lca, p1, p2, ans; i <= q; ++i) {
    scanf("%d", &type);
    events[i] = events[i - 1];
    if (type == 1) {
      scanf("%d", &u);
      events[i] = buildTree(events[i], vertices[u].inTime, 1, 1, (2 * n));
      events[i] = buildTree(events[i], vertices[u].outTime, -1, 1, (2 * n));
    } else {
      scanf("%d %d %d %d", &u, &v, &k, &y);
      lca = findLCA(u, v);
      p1 = getGoodNodes(events[i], events[y], u, lca);
      p2 = getGoodNodes(events[i], events[y], v, lca);
      k += getGoodNodes(events[i], events[y], u, u);
      if (p1 + p2 - getGoodNodes(events[i], events[y], lca, lca) < k)
        ans = -1;
      else {
        if (k <= p1)
          ans = getKthGoodNode(events[i], events[y], u, lca, k);
        else {
          k -= p1;
          p2 -= getGoodNodes(events[i], events[y], lca, lca);
          k = p2 - k + 1;
          ans = getKthGoodNode(events[i], events[y], v, lca, k);
        }
      }
      if (ans == v)
        ans = -1;
      printf("%d\n", ans);
    }
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
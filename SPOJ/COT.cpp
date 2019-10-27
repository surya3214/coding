// AC Persistent Segment Tree
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define H_MAX 19
#define N_MAX (int) (1e5)
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
struct N {
  int l, r, cnt;
  N() {}
  N(int l, int r, int cnt) : l(l), r(r), cnt(cnt) {}
} nodes[BUFF(NODES_MAX)];
int n, nodes_ptr;
int w[BUFF(N_MAX)], roots[BUFF(N_MAX)], parent[BUFF(N_MAX)][BUFF(H_MAX)], depth[BUFF(N_MAX)];
map<int, int> M;
int RM[BUFF(N_MAX)];
vector<int> adj[BUFF(N_MAX)];
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
void dfs(int cur, int prev) {
  parent[cur][0] = prev;
  for (int i = 1, x; i < H_MAX; ++i) {
    x = parent[cur][i - 1];
    parent[cur][i] = x ? parent[x][i - 1] : 0;
  }
  depth[cur] = 1 + depth[prev];
  roots[cur] = buildTree(roots[prev], M[w[cur]], 1, n);
  for (auto next: adj[cur]) {
    if (next != prev)
      dfs(next, cur);
  }
}
void process() {
  dfs(1, 0);
}
int LCA(int u, int v) {
  if (depth[u] < depth[v])
    swap(u, v);
  int diff = depth[u] - depth[v];
  for (int i = H_MAX - 1; i >= 0 && diff; --i) {
    if (diff >= (1 << i)) {
      u = parent[u][i];
      diff -= (1 << i);
    }
  }
  if (u != v) {
    for (int i = H_MAX - 1; i >= 0; --i) {
      if (parent[u][i] != parent[v][i]) {
        u = parent[u][i];
        v = parent[v][i];
      }
    }
    u = parent[u][0];
  }
  return u;
}
int getKth(int a, int b, int c, int d, int k, int l, int r) {
  if (l == r)
    return RM[l];
  int cnt = nodes[nodes[a].l].cnt + nodes[nodes[b].l].cnt - nodes[nodes[c].l].cnt - nodes[nodes[d].l].cnt;
  int mid = getMid(l, r);
  if (k <= cnt)
    return getKth(nodes[a].l, nodes[b].l, nodes[c].l, nodes[d].l, k, l, mid);
  else return getKth(nodes[a].r, nodes[b].r, nodes[c].r, nodes[d].r, k - cnt, mid + 1, r);
}
void program() {
  int m;
  vector<int> input;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &w[i]);
    input.push_back(w[i]);
  }
  sort(input.begin(), input.end());
  int maxi = 1;
  for (auto it = input.begin(); it != input.end(); ++it, ++maxi) {
    M[*it] = maxi;
    RM[maxi] = *it;
  }
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d %d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  process();
  for (int i = 1, u, v, k, lca; i <= m; ++i) {
    scanf("%d %d %d", &u, &v, &k);
    lca = LCA(u, v);
    printf("%d\n", getKth(roots[u], roots[v], roots[lca], roots[parent[lca][0]], k, 1, n));
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}
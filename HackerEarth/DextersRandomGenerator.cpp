// AC Persistent Trie on Bits, LCA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define BITS_MAX 30
#define N_MAX (int) 1e5
#define H_MAX (int) 17
#define NODES_MAX (int) (2 * N_MAX * BUFF(BITS_MAX))
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
struct {
  int val, depth;
  int parent[BUFF(H_MAX)];
  char binary[BUFF(BITS_MAX)];
  vector<int> edges;
} vertices[BUFF(N_MAX)];
struct {
  int cnt, next[2];
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(N_MAX)];
char buffer[BUFF(BITS_MAX)]; // used by the trie searching functions
int buildTree(int prev, int idx) {
  int cur, ret;
  ret = cur = ++nodes_ptr;
  nodes[cur] = nodes[prev];
  ++nodes[cur].cnt;
  bool x;
  for (int i = 0; i < BITS_MAX; ++i) { // parsing 30 bits
    x = vertices[idx].binary[i] == '1';
    nodes[cur].next[x] = ++nodes_ptr;
    prev = nodes[prev].next[x];
    cur = nodes[cur].next[x];
    nodes[cur] = nodes[prev];
    ++nodes[cur].cnt;
  }
  return ret;
}
void convertToBinary(int u) {
  vertices[u].binary[BITS_MAX] = '\0';
  int x = vertices[u].val;
  for (int i = BITS_MAX - 1; i >= 0; --i, x >>= 1)
    vertices[u].binary[i] = (x & 1) ? '1' : '0';
}
void dfs(int cur, int prev) {
  vertices[cur].depth = vertices[prev].depth + 1;
  vertices[cur].parent[0] = prev;
  for (int i = 1, x; i <= H_MAX; ++i) {
    x = vertices[cur].parent[i - 1];
    vertices[cur].parent[i] = x ? vertices[x].parent[i - 1] : 0;
  }
  roots[cur] = buildTree(roots[prev], cur);
  for (auto next: vertices[cur].edges)
    if (next != prev)
      dfs(next, cur);
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
void copyToBuffer(int u) {
  for (int i = 0; i <= BITS_MAX; ++i)
    buffer[i] = vertices[u].binary[i];
}
int decimalifyBuffer() {
  int ret = 0;
  for (int i = BITS_MAX - 1, cur_rep = 1; i >= 0; --i, cur_rep <<= 1) {
    if (buffer[i] == '1')
      ret += cur_rep;
  }
  return ret;
}
int queryValue(int u_r, int v_r, int lca_r, int p_lca_r) {
  bool x;
  char looking_for;
  for (int i = 0, cnt, a, b, c, d; i < BITS_MAX; ++i) {
    looking_for = (buffer[i] == '1') ? '0' : '1';
    x = looking_for == '1';
    a = nodes[nodes[u_r].next[x]].cnt;
    b = nodes[nodes[p_lca_r].next[x]].cnt;
    c = nodes[nodes[v_r].next[x]].cnt;
    d = nodes[nodes[lca_r].next[x]].cnt;
    cnt = a - b + c - d;
    if (!cnt)
      x = !x;
    u_r = nodes[u_r].next[x];
    v_r = nodes[v_r].next[x];
    lca_r = nodes[lca_r].next[x];
    p_lca_r = nodes[p_lca_r].next[x];
    buffer[i] = x ? '1': '0';
  }
  return decimalifyBuffer();
}
int queryAns(int u, int v) {
  int lca, p_lca, ret_max, ret_min;
  lca = findLCA(u, v), p_lca = vertices[lca].parent[0];
  copyToBuffer(u);
  ret_max = vertices[u].val ^ queryValue(roots[u], roots[v], roots[lca], roots[p_lca]);
  copyToBuffer(v);
  ret_max = max(ret_max, vertices[v].val ^ queryValue(roots[u], roots[v], roots[lca], roots[p_lca]));
  return ret_max;
}
void program() {
  int q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &vertices[i].val);
    convertToBinary(i);
  }
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d %d", &u, &v);
    vertices[u].edges.push_back(v);
    vertices[v].edges.push_back(u);
  }
  dfs(1, 0);
  for (int i = 1, u, v; i <= q; ++i) {
    scanf("%d %d", &u, &v);
    printf("%d\n", queryAns(u, v));
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
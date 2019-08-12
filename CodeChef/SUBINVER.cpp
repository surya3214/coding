// AC Persistent Segment Tree
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
ll m_hash[BUFF(N_MAX)];
struct N {
  int l, r;
  bool dirty;
  ll zeros_hash, ones_hash;
  N() {}
  N(int l, int r, ll z_h, ll o_h, bool dirty = false) : l(l), r(r), zeros_hash(z_h), ones_hash(o_h), dirty(dirty) {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr, best;
int roots[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
void buildBase(int cur, int l, int r) {
  ll z_h;
  if (l == r) {
    z_h = m_hash[l];
    nodes[cur] = N(0, 0, z_h, 0);
  } else {
    int mid = getMid(l, r);
    if (!nodes[cur].l)
      nodes[cur].l = ++nodes_ptr;
    if (!nodes[cur].r)
      nodes[cur].r = ++nodes_ptr;
    int a = nodes[cur].l;
    int b = nodes[cur].r;
    buildBase(a, l, mid);
    buildBase(b, mid + 1, r);
    z_h = nodes[a].zeros_hash ^ nodes[b].zeros_hash;
    nodes[cur] = N(a, b, z_h, 0);
  }
}
void process() {
  mt19937 m_rand(time(0));
  for (int i = 1; i <= n; ++i) {
    m_hash[i] = m_rand();
    while (m_hash[i] == 0)
      m_hash[i] = m_rand();
  }
  buildBase(roots[0], 1, n);
}
void pushDown(int cur) {
  if (!nodes[cur].dirty)
    return;
  int new_child, child;
  ll z_h, o_h;
  child = nodes[cur].l;
  if (child) {
    new_child = ++nodes_ptr;
    z_h = nodes[child].ones_hash, o_h = nodes[child].zeros_hash;
    nodes[new_child] = N(nodes[child].l, nodes[child].r, z_h, o_h, !nodes[child].dirty);
    nodes[cur].l = new_child;
  }
  child = nodes[cur].r;
  if (child) {
    new_child = ++nodes_ptr;
    z_h = nodes[child].ones_hash, o_h = nodes[child].zeros_hash;
    nodes[new_child] = N(nodes[child].l, nodes[child].r, z_h, o_h, !nodes[child].dirty);
    nodes[cur].r = new_child;
  }
  nodes[cur].dirty = false;
}
int buildTree(int prev, int sl, int sr, int l, int r) {
  if (sr < l || r < sl)
    return prev;
  int cur = ++nodes_ptr;
  ll z_h, o_h;
  if (sl <= l && r <= sr) {
    z_h = nodes[prev].ones_hash;
    o_h = nodes[prev].zeros_hash;
    nodes[cur] = N(nodes[prev].l, nodes[prev].r, z_h, o_h, !nodes[prev].dirty);
  } else {
    int mid = getMid(l, r);
    pushDown(prev);
    int a = buildTree(nodes[prev].l, sl, sr, l, mid);
    int b = buildTree(nodes[prev].r, sl, sr, mid + 1,r );
    ll z_h, o_h;
    z_h = nodes[a].zeros_hash ^ nodes[b].zeros_hash;
    o_h = nodes[a].ones_hash ^ nodes[b].ones_hash;
    nodes[cur] = N(a, b, z_h, o_h);
  }
  return cur;
}
bool isBigger(int x, int y, int l, int r) {
  if (l == r) {
    return (bool) (nodes[x].ones_hash && nodes[y].zeros_hash);
  } else {
    pushDown(x);
    pushDown(y);
    int mid = getMid(l, r);
    int a = nodes[x].l;
    int b = nodes[y].l;
    if (nodes[a].zeros_hash == nodes[b].zeros_hash)
      return isBigger(nodes[x].r, nodes[y].r, mid + 1, r);
    else return isBigger(a, b, l, mid);
  }
}
void dfs(int ptr, int l, int r) {
  pushDown(ptr);
  if (l == r) {
    int x = (bool) (nodes[ptr].ones_hash);
    printf("%d", x);
  } else {
    int mid = getMid(l, r);
    dfs(nodes[ptr].l, l, mid);
    dfs(nodes[ptr].r, mid + 1, r);
  }
}
void program() {
  int q;
  scanf("%d %d", &n, &q);
  process();
  for (int i = 1, l, r; i <= q; ++i) {
    scanf("%d %d", &l, &r);
    roots[i] = buildTree(roots[i - 1], l, r, 1, n);
    if (isBigger(roots[i], roots[best], 1, n))
      best = i;
  }
  dfs(roots[best], 1, n);
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}
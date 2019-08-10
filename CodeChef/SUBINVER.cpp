// NA
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
  N(int l, int r, ll z_h, ll o_h, bool dirty) : l(l), r(r), zeros_hash(z_h), ones_hash(o_h), dirty(dirty) {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr, best;
int roots[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildBase(int l, int r) {
  int cur = ++nodes_ptr;
  ll z_h;
  if (l == r) {
    z_h = m_hash[l];
    nodes[cur] = N(0, 0, z_h, 0, false);
  } else {
    int mid = getMid(l, r);
    int a = buildBase(l, mid);
    int b = buildBase(mid + 1, r);
    z_h = nodes[a].zeros_hash ^ nodes[b].zeros_hash;
    nodes[cur] = N(a, b, z_h, 0, false);
  }
  return cur;
}
void process() {
  mt19937 m_rand(time(0));
  for (int i = 1; i <= n; ++i) {
    m_hash[i] = m_rand();
    while (m_hash[i] == 0)
      m_hash[i] = m_rand();
  }
  roots[0] = buildBase(1, n);
}
void sanitize(int ptr) {
  if (!nodes[ptr].dirty)
    return;
  int l, r, cur, child;
  ll z_h, o_h;
  child = nodes[ptr].l;
  if (child) {
    cur = ++nodes_ptr;
    l = nodes[child].l, r = nodes[child].r, z_h = nodes[child].ones_hash, o_h = nodes[child].zeros_hash;
    nodes[cur] = N(l, r, z_h, o_h, true);
  }
  child = nodes[ptr].r;
  if (child) {
    cur = ++nodes_ptr;
    l = nodes[child].l, r = nodes[child].r, z_h = nodes[child].ones_hash, o_h = nodes[child].zeros_hash;
    nodes[cur] = N(l, r, z_h, o_h, true);
  }
  nodes[ptr].dirty = false;
}
int buildTree(int prev, int sl, int sr, int l, int r) {
  if (sl <= l && r <= sr) {
    int cur = ++nodes_ptr;
    ll z_h, o_h;
    z_h = nodes[prev].ones_hash;
    o_h = nodes[prev].zeros_hash;
    nodes[cur] = N(nodes[prev].l, nodes[prev].r, z_h, o_h, !nodes[prev].dirty);
    return cur;
  } else if (l <= sl && sr <= r) {
    int mid = getMid(l, r);
    sanitize(nodes[prev].l);
    sanitize(nodes[prev].r);
    int a = buildTree(nodes[prev].l, sl, sr, l, mid);
    int b = buildTree(nodes[prev].r, sl, sr, mid + 1,r );
    ll z_h, o_h;
    z_h = nodes[a].zeros_hash ^ nodes[b].zeros_hash;
    o_h = nodes[a].ones_hash ^ nodes[b].ones_hash;
    int cur = ++nodes_ptr;
    nodes[cur] = N(a, b, z_h, o_h, false);
    return cur;
  }
  return prev;
}
bool isBigger(int a_ptr, int b_ptr, int l, int r) {
  sanitize(a_ptr);
  sanitize(b_ptr);
  if (l == r) {
    return (bool)(nodes[a_ptr].ones_hash && nodes[b_ptr].zeros_hash);
  } else {
    int mid = getMid(l, r);
    if (nodes[a_ptr].zeros_hash == nodes[b_ptr].zeros_hash)
      return isBigger(nodes[a_ptr].r, nodes[b_ptr].r, mid + 1, r);
    else return isBigger(nodes[a_ptr].l, nodes[b_ptr].l, l, mid);
  }
}
void dfs(int ptr, int l, int r) {
  sanitize(ptr);
  if (l == r) {
    int x = (bool)(nodes[ptr].ones_hash);
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
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}
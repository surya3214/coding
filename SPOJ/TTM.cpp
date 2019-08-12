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
int n, input[BUFF(N_MAX)];
struct N {
  int l, r;
  ll sum, dirty;
  N() {}
  N(int l, int r, ll sum, ll dirty = 0) : l(l), r(r), sum(sum), dirty(dirty) {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr, cur_state;
int roots[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int getLength(int l, int r) { return (r - l + 1); }
void buildBase(int ptr, int val, int pos, int l, int r) {
  if (l <= pos && pos <= r) {
    if (l == r)
      nodes[ptr].sum = val;
    else {
      int mid = getMid(l, r), a, b;
      if (!nodes[ptr].l)
        nodes[ptr].l = ++nodes_ptr;
      if (!nodes[ptr].r)
        nodes[ptr].r = ++nodes_ptr;
      a = nodes[ptr].l;
      b = nodes[ptr].r;
      buildBase(a, val, pos, l, mid);
      buildBase(b, val, pos, mid + 1, r);
      nodes[ptr] = N(a, b, nodes[a].sum + nodes[b].sum);
    }
  }
}
void pushDown(int cur, int l, int r) {
  if (!nodes[cur].dirty || l == r)
    return;
  int new_child, mid, child;
  ll sum, dirty;
  mid = getMid(l, r);
  child = nodes[cur].l;
  if (child) {
    new_child = ++nodes_ptr;
    sum = nodes[child].sum + (nodes[cur].dirty * getLength(l, mid));
    dirty = nodes[child].dirty + nodes[cur].dirty;
    nodes[new_child] = N(nodes[child].l, nodes[child].r, sum, dirty);
    nodes[cur].l = new_child;
  }
  child = nodes[cur].r;
  if (child) {
    new_child = ++nodes_ptr;
    sum = nodes[child].sum + (nodes[cur].dirty * getLength(mid + 1, r));
    dirty = nodes[child].dirty + nodes[cur].dirty;
    nodes[new_child] = N(nodes[child].l, nodes[child].r, sum, dirty);
    nodes[cur].r = new_child;
  }
  nodes[cur].dirty = 0;
}
int buildTree(int prev, int val, int sl, int sr, int l, int r) {
  if (sr < l || r < sl)
    return prev;
  int cur = ++nodes_ptr;
  if (sl <= l && r <= sr) {
    ll sum = nodes[prev].sum + (1LL * val * getLength(l, r));
    nodes[cur] = N(nodes[prev].l, nodes[prev].r, sum, nodes[prev].dirty + val);
  } else {
    pushDown(prev, l, r);
    int mid = getMid(l, r);
    int a = buildTree(nodes[prev].l, val, sl, sr, l, mid);
    int b = buildTree(nodes[prev].r, val, sl, sr, mid + 1, r);
    nodes[cur] = N(a, b, nodes[a].sum + nodes[b].sum);
  }
  return cur;
}
ll querySum(int ptr, int sl, int sr, int l, int r) {
  if (sr < l || r < sl)
    return 0;
  if (sl <= l && r <= sr)
    return nodes[ptr].sum;
  else {
    pushDown(ptr, l, r);
    int mid = getMid(l, r);
    ll a = querySum(nodes[ptr].l, sl, sr, l, mid);
    ll b = querySum(nodes[ptr].r, sl, sr, mid + 1, r);
    return a + b;
  }
}
void program() {
  int q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i]);
    buildBase(roots[cur_state], input[i], i, 1, n);
  }
  char type;
  for (int i = 1, l, r, t; i <= q; ++i) {
    scanf(" %c ", &type);
    switch (type) {
      case 'C':
        scanf("%d %d %d", &l, &r, &t);
        ++cur_state;
        roots[cur_state] = buildTree(roots[cur_state - 1], t, l, r, 1, n);
        break;
      case 'Q':
        scanf("%d %d", &l, &r);
        printf("%lld\n", querySum(roots[cur_state], l, r, 1, n));
        break;
      case 'H':
        scanf("%d %d %d", &l, &r, &t);
        printf("%lld\n", querySum(roots[t], l, r, 1, n));
        break;
      case 'B':
        scanf("%d", &t);
        cur_state = t;
        break;
    }
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}
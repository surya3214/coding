// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 5e5
#define VAL_MAX (int) 5e5
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#define INF (N_MAX + 1)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
struct {
  int val, prev; // val -> raw value provided in input, prev -> value it represents in the tree
} positions[BUFF(N_MAX)];
int t_prev[BUFF(VAL_MAX)];
struct N {
  N() {}
  N(int l, int r, int min_v, int min_idx) : l(l), r(r), min_v(min_v), min_idx(min_idx) {}
  int l, r, min_v, min_idx;
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int pos, int val, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    if (l == r) {
      nodes[cur].min_v = val;
      nodes[cur].min_idx = pos;
    } else {
      int mid = getMid(l, r);
      int a = buildTree(nodes[prev].l, pos, val, l, mid);
      int b = buildTree(nodes[prev].r, pos, val, mid + 1, r);
      int a_val = (a) ? nodes[a].min_v : INF;
      int b_val = (b) ? nodes[b].min_v : INF;
      int min_val, min_idx;
      if (a_val < b_val)
        min_val = a_val, min_idx = nodes[a].min_idx;
      else min_val = b_val, min_idx = nodes[b].min_idx;
      nodes[cur] = N(a, b, min_val, min_idx);
    }
    return cur;
  }
  return prev;
}
int queryLowestIndex(int cur, int t_l, int t_r, int l, int r) {
  if (!cur || t_r < l || r < t_l)
    return INF;
  else if (t_l <= l && r <= t_r)
    return nodes[cur].min_idx;
  else {
    int mid = getMid(l, r);
    int a = queryLowestIndex(nodes[cur].l, t_l, t_r, l, mid);
    int b = queryLowestIndex(nodes[cur].r, t_l, t_r, mid + 1, r);
    return (positions[a].prev < positions[b].prev) ? a : b;
  }
}
int getOneOccurrenceNumber(int l, int r) {
  int lowest_idx = queryLowestIndex(roots[r], l, r, 1, n);
  if (positions[lowest_idx].prev == lowest_idx || positions[lowest_idx].prev < l)
    return lowest_idx;
  return 0;
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &positions[i].val);
    roots[i] = roots[i - 1];
    if (t_prev[positions[i].val])
      roots[i] = buildTree(roots[i], t_prev[positions[i].val], INF, 1, n);
    positions[i].prev = (t_prev[positions[i].val]) ? t_prev[positions[i].val] : i;
    roots[i] = buildTree(roots[i], i, positions[i].prev, 1, n);
    t_prev[positions[i].val] = i;
  }
  int q;
  scanf("%d", &q);
  for (int i = 1, l, r; i <= q; ++i) {
    scanf("%d %d", &l, &r);
    printf("%d\n", getOneOccurrenceNumber(l, r));
  }
}
void ready() { positions[INF].prev = INF; }
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  ready();
  program();
  return 0;
}
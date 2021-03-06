// AC Segment Tree, Input manipulation, Range query
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define FREQ_MAX (int) (1e4 + 1e2)
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n, k;
struct S {
  int x, r, f, tree_pos;
  bool operator <(S other) { return r > other.r; }
} stations[BUFF(N_MAX)];
struct P {
  int idx, pos;
  bool operator <(P other) { return pos < other.pos; }
} positions[BUFF(N_MAX)];
ll bad_pairs;
struct N {
  int l, r, cnt;
  N() {}
  N(int l, int r, int cnt) : l(l), r(r), cnt(cnt) {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(FREQ_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int cur, int pos, int l, int r) {
  if (l <= pos && pos <= r) {
    if (!cur)
      cur = ++nodes_ptr;
    if (l == r)
      ++nodes[cur].cnt;
    else {
      int mid = getMid(l, r);
      int a = buildTree(nodes[cur].l, pos, l, mid);
      int b = buildTree(nodes[cur].r, pos, mid + 1, r);
      nodes[cur] = N(a, b, nodes[a].cnt + nodes[b].cnt);
    }
  }
  return cur;
}
int queryCount(int cur, int t_l, int t_r, int l, int r) {
  if (!cur || r < t_l || t_r < l)
    return 0;
  else if (t_l <= l && r <= t_r)
    return nodes[cur].cnt;
  else {
    int mid = getMid(l, r);
    int a = queryCount(nodes[cur].l, t_l, t_r, l, mid);
    int b = queryCount(nodes[cur].r, t_l, t_r, mid + 1, r);
    return a + b;
  }
}
int getLowerBound(int x) {
  // returns the first position[1..n] with x <= val
  if (x <= 0)
    return 1;
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (x <= positions[mid].pos)
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
int getUpperBound(int x) {
  // returns the last position[1..n] with val <= x
  if (positions[n].pos <= x)
    return n;
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (positions[mid].pos <= x)
      l = mid + 1;
    else r = mid - 1;
  }
  return l - 1;
}
void solve() {
  for (int i = 1, f_l, f_r, pos_l, pos_r; i <= n; ++i) {
    f_l = stations[i].f - k;
    f_r = stations[i].f + k;
    pos_l = getLowerBound(stations[i].x - stations[i].r);
    pos_r = getUpperBound(stations[i].x + stations[i].r);
    for (int j = max(1, f_l); j <= f_r; ++j)
      bad_pairs += queryCount(roots[j], pos_l, pos_r, 1, n);
    roots[stations[i].f] = buildTree(roots[stations[i].f], stations[i].tree_pos, 1, n);
  }
}
void program() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %d", &stations[i].x, &stations[i].r, &stations[i].f);
    positions[i].idx = i;
    positions[i].pos = stations[i].x;
  }
  sort(positions + 1, positions + 1 + n);
  for (int i = 1; i <= n; ++i)
    stations[positions[i].idx].tree_pos = i;
  sort(stations + 1, stations + 1 + n);
  solve();
  printf("%lld\n", bad_pairs);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
} 
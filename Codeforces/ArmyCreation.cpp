// AC F yeah! Persistent Segment Tree
// Notes: Had to give special attention to "0" value
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define Q_MAX (int) 1e5
#define VAL_MAX (int) 1e5
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n, k;
int types[BUFF(N_MAX)];
struct N {
  int l, r, cnt;
  N() {}
  N(int l, int r, int cnt) : l(l), r(r), cnt(cnt) {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(N_MAX)];
queue<int> q[BUFF(VAL_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int pos, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    if (l == r)
      nodes[cur].cnt = nodes[prev].cnt + 1;
    else {
      int mid = getMid(l, r);
      int a = buildTree(nodes[prev].l, pos, l, mid);
      int b = buildTree(nodes[prev].r, pos, mid + 1, r);
      nodes[cur] = N(a, b, nodes[a].cnt + nodes[b].cnt);
    }
    return cur;
  }
  return prev;
}
void process() {
  for (int i = 1, kth_prev, x; i <= n; ++i) {
    x = types[i];
    q[x].push(i);
    if (q[x].size() <= k)
      kth_prev = 1;
    else {
      kth_prev = q[x].front() + 1;
      q[x].pop();
    }
    roots[i] = buildTree(roots[i - 1], kth_prev, 1, n);
  }
}
int querySum(int a_ptr, int b_ptr, int until, int l, int r) {
  if (r <= until)
    return nodes[a_ptr].cnt - nodes[b_ptr].cnt;
  else if (until < l)
    return 0;
  else {
    int mid = getMid(l, r);
    int a = querySum(nodes[a_ptr].l, nodes[b_ptr].l, until, l, mid);
    int b = querySum(nodes[a_ptr].r, nodes[b_ptr].r, until, mid + 1, r);
    return a + b;
  }
}
void program() {
	scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &types[i]);
  process();
  int q;
  scanf("%d", &q);
  for (int i = 1, l, r, last = 0; i <= q; ++i) {
    scanf("%d %d", &l, &r);
    l = (l + last);
    while (l >= n)
      l -= n;
    ++l;
    r = (r + last);
    while (r >= n)
      r -= n;
    ++r;
    if (l > r)
      swap(l, r);
    last = querySum(roots[r], roots[l - 1], l, 1, n);
    printf("%d\n", last);
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
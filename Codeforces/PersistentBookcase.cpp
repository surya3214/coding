// AC Persistent Segment Tree, Lazy Propagation
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define POS_MAX (int) 1e6
#define Q_MAX (int) (1e5)
#define NODES_MAX (int) (log2(POS_MAX) * POS_MAX)
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n, m;
struct N {
  int l, r, cnt;
  bool lazy;
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int t_roots[BUFF(Q_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
void pushDown(int cur, int l, int r) {
  if (!nodes[cur].lazy)
    return;
  int mid = getMid(l, r);
  int next;
  next = ++nodes_ptr;
  nodes[next] = nodes[nodes[cur].l];
  nodes[next].cnt = (mid - l + 1) - nodes[next].cnt;
  nodes[next].lazy = !nodes[next].lazy;
  nodes[cur].l = next;
  next = ++nodes_ptr;
  nodes[next] = nodes[nodes[cur].r];
  nodes[next].cnt = (r - (mid + 1) + 1) - nodes[next].cnt;
  nodes[next].lazy = !nodes[next].lazy;
  nodes[cur].r = next;
  nodes[cur].lazy = false;
}
int updateBook(int prev, bool add, int pos, int l, int r) {
  int cur = ++nodes_ptr;
  pushDown(prev, l, r);
  nodes[cur] = nodes[prev];
  if (l == r) {
    if (add)
      nodes[cur].cnt = 1;
    else nodes[cur].cnt = 0;
  } else {
    int mid = getMid(l, r);
    if (pos <= mid)
      nodes[cur].l = updateBook(nodes[prev].l, add, pos, l, mid);
    else nodes[cur].r = updateBook(nodes[prev].r, add, pos, mid + 1, r);
    nodes[cur].cnt = nodes[nodes[cur].l].cnt + nodes[nodes[cur].r].cnt;
  }
  return cur;
}
int flipBooks(int prev, int sl, int sr, int l, int r) {
  if (r < sl || sr < l)
    return prev;
  int cur = ++nodes_ptr;
  pushDown(prev, l, r);
  nodes[cur] = nodes[prev];
  if (sl <= l && r <= sr) {
    nodes[cur].cnt = (r - l + 1) - nodes[cur].cnt;
    nodes[cur].lazy = !nodes[cur].lazy;
  } else {
    int mid = getMid(l, r);
    nodes[cur].l = flipBooks(nodes[prev].l, sl, sr, l, mid);
    nodes[cur].r = flipBooks(nodes[prev].r, sl, sr, mid + 1, r);
    nodes[cur].cnt = nodes[nodes[cur].l].cnt + nodes[nodes[cur].r].cnt;
  }
  return cur;
}
void program() {
  int q;
  scanf("%d %d %d", &n, &m, &q);
  for (int i, j, k, type, pos, state = 1, r = (n * m); q; --q, ++state) {
    scanf("%d", &type);
    switch (type) {
      case 1:
        scanf("%d %d", &i, &j);
        pos = (i - 1) * m + j;
        t_roots[state] = updateBook(t_roots[state - 1], true, pos, 1, r);
        break;
      case 2:
        scanf("%d %d", &i, &j);
        pos = (i - 1) * m + j;
        t_roots[state] = updateBook(t_roots[state - 1], false, pos, 1, r);
        break;
      case 3:
        scanf("%d", &i);
        t_roots[state] = flipBooks(t_roots[state - 1], (i - 1) * m + 1, i * m, 1, r);
        break;
      case 4:
        scanf("%d", &k);
        t_roots[state] = t_roots[k];
        break;
    }
    printf("%d\n", nodes[t_roots[state]].cnt);
  }
}
int main() {
#ifndef ONLINE_JUDGE
  // freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
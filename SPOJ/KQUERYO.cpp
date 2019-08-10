// AC Persistent Segment Trees, Binary Search
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 3e4
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, ans;
struct I {
  int val, idx;
  bool operator <(I& other) {
    return val < other.val;
  }
} input[BUFF(N_MAX)];
struct N {
  int cnt, l, r;
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int pos, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    if (l == r)
      nodes[cur].cnt = 1;
    else {
      int mid = getMid(l, r);
      nodes[cur].l = buildTree(nodes[prev].l, pos, l, mid);
      nodes[cur].r = buildTree(nodes[prev].r, pos, mid + 1, r);
      nodes[cur].cnt = nodes[nodes[cur].l].cnt + nodes[nodes[cur].r].cnt;
    }
    return cur;
  }
  return prev;
}
void process() {
  sort(input + 1, input + 1 + n);
  for (int x = 1; x <= n; ++x)
    roots[x] = buildTree(roots[x - 1], input[x].idx, 1, n);
}
int getCountIn(int pos, int sl, int sr, int l, int r) {
  if (sr < l || r < sl)
    return 0;
  else if (sl <= l && r <= sr)
    return nodes[pos].cnt;
  else {
    int mid = getMid(l, r);
    int x = getCountIn(nodes[pos].l, sl, sr, l, mid);
    int y = getCountIn(nodes[pos].r, sl, sr, mid + 1, r);
    return x + y;
  }
}
int getRightMostIndex(int val) {
  int l = 1, r = n, mid;
  while (l <= r) {
    mid = getMid(l, r);
    if (val < input[mid].val)
      r = mid - 1;
    else l = mid + 1;
  }
  return l - 1;
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i].val);
    input[i].idx = i;
  }
  process();
  int q;
  scanf("%d", &q);
  for (int i = 1, a, b, c, x, y; i <= q; ++i) {
    scanf("%d %d %d", &a, &b, &c);
    a = a ^ ans;
    b = b ^ ans;
    c = c ^ ans;
    a = (a < 1) ? 1 : a;
    b = (b > n) ? n : b;
    if (a > b)
      ans = 0;
    else {
      int pos = getRightMostIndex(c);
      x = getCountIn(roots[n], a, b, 1, n);
      y = getCountIn(roots[pos], a, b, 1, n);
      ans = x - y;
    }
    printf("%d\n", ans);
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}
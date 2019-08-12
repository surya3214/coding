// AC Persistent Segment Tree
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (1e5)
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
pii V[BUFF(N_MAX)];
int RM[BUFF(N_MAX)];
struct N {
  int cnt, l, r;
  N() {}
  N(int l, int r, int cnt) : cnt(cnt), l(l), r(r) {}
} nodes[BUFF(NODES_MAX)];
int input[BUFF(N_MAX)], roots[BUFF(N_MAX)];
int n, nodes_ptr;
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int pos, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    if (l == r)
      nodes[cur] = N(0, 0, 1);
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
  sort(V + 1, V + 1 + n);
  for (int i = n; i; --i) {
    roots[i] = buildTree(roots[i + 1], V[i].second, 1, n);
    RM[V[i].second] = V[i].first;
  }
}
int getKthNumber(int ptr, int k, int l, int r) {
  if (l == r)
    return RM[l];
  int a, b;
  a = nodes[ptr].l;
  b = nodes[ptr].r;
  int mid = getMid(l, r);
  if (k <= nodes[a].cnt)
    return getKthNumber(a, k, l, mid);
  else return getKthNumber(b, k - nodes[a].cnt, mid + 1, r);
}
int getLeftMost(int val) {
  int l = 1, r = n, mid;
  while (l <= r) {
    mid = getMid(l, r);
    if (V[mid].first >= val)
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
void program() {
  int q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i]);
    V[i] = pii(input[i], i);
  }
  process();
  for (int i = 1, l, k, cur; i <= q; ++i) {
    scanf("%d %d", &l, &k);
    cur = getLeftMost(l);
    printf("%d\n", getKthNumber(roots[cur], k, 1, n));
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}
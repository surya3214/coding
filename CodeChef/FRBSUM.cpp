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
int n, input[BUFF(N_MAX)];
pii V[BUFF(N_MAX)];
struct N {
  int l, r, sum;
  N() {}
  N(int l, int r, int sum) : sum(sum), l(l), r(r) {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int val, int pos, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    if (l == r)
      nodes[cur].sum = val;
    else {
      int mid = getMid(l, r);
      int a = buildTree(nodes[prev].l, val, pos, l, mid);
      int b = buildTree(nodes[prev].r, val, pos, mid + 1, r);
      nodes[cur] = N(a, b, nodes[a].sum + nodes[b]. sum);
    }
    return cur;
  }
  return prev;
}
void process() {
  sort(V + 1, V + 1 + n);
  for (int i = 1; i <= n; ++i)
    roots[i] = buildTree(roots[i - 1], V[i].first, V[i].second, 1, n);
}
int querySum(int ptr, int sl, int sr, int l, int r) {
  if (sr < l || r < sl)
    return 0;
  else if (sl <= l && r <= sr)
    return nodes[ptr].sum;
  else {
    int mid = getMid(l, r);
    int a = querySum(nodes[ptr].l, sl, sr, l, mid);
    int b = querySum(nodes[ptr].r, sl, sr, mid + 1, r);
    return a + b;
  }
}
int solve(int l, int r) {
  int ret = 1, id, cur;
  while (1) {
    id = upper_bound(V + 1, V + 1 + n, pii(ret, n + 1)) - (V + 1);
    cur = querySum(roots[id], l, r, 1, n);
    if (cur < ret)
      break;
    else ret = cur + 1;
  }
  return ret;
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i]);
    V[i] = pii(input[i], i);
  }
  process();
  int q;
  scanf("%d", &q);
  for (int i = 1, l, r; i <= q; ++i) {
    scanf("%d %d", &l, &r);
    printf("%d\n", solve(l, r));
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}
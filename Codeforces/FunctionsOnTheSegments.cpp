// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 75000
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#define MOD (int) 1e9
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
struct X {
  X() {}
  X(int idx, int val) : idx(idx), val(val) {}
  bool operator <(X other) { return val < other.val; }
  int idx, val;
} x1s[BUFF(N_MAX)], x2s[BUFF(N_MAX)];
struct N {
  N() {}
  N(int l, int r, ll y, ll a, ll b) : l(l), r(r), y(y), a(a), b(b) {}
  int l, r;
  ll y, a, b;
} nodes[BUFF(2 * NODES_MAX)];
int nodes_ptr;
struct {
  int x1, x2, y1, y2, a, b;
  int x1_pos, x2_pos;
} input[BUFF(N_MAX)];
int x1s_roots[BUFF(N_MAX)], x2s_roots[BUFF(N_MAX)];
struct {
  ll y, a, b;
} buffer;
void rollOver(ll &x) {
  if (x >= MOD)
    x %= MOD;
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int pos, int y, int a, int b, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    if (l == r)
      nodes[cur] = N(0, 0, y, a, b);
    else {
      int mid = getMid(l, r);
      int t_l = buildTree(nodes[prev].l, pos, y, a, b, l, mid);
      int t_r = buildTree(nodes[prev].r, pos, y, a, b, mid + 1, r);
      nodes[cur] = N(t_l, t_r, nodes[t_l].y + nodes[t_r].y, nodes[t_l].a + nodes[t_r].a, nodes[t_l].b + nodes[t_r].b);
      rollOver(nodes[cur].y);
      rollOver(nodes[cur].a);
      rollOver(nodes[cur].b);
    }
    return cur;
  }
  return prev;
}
void process() {
  sort(x1s + 1, x1s + 1 + n);
  sort(x2s + 1, x2s + 1 + n);
  for (int i = 1; i <= n; ++i) {
    input[x1s[i].idx].x1_pos = i;
    input[x2s[i].idx].x2_pos = i;
  }
  for (int i = 1; i <= n; ++i) {
    x1s_roots[i] = buildTree(x1s_roots[i - 1], input[i].x1_pos, input[i].y1, input[i].a, input[i].b, 1, n);
    x2s_roots[i] = buildTree(x2s_roots[i - 1], input[i].x2_pos, input[i].y2, input[i].a, input[i].b, 1, n);
  }
}
void resetBuffer() { buffer.a = buffer.b = buffer.y = 0; }
ll queryAns(int l, int r, ll x) {
  int pos;
  ll ret = 0;
  pos = getUpperBound(x, true);
  resetBuffer();
  buildBuffer(roots[r], roots[l - 1], true, 1, pos, 1, n);
  ret += buffer.y;
  rollOver(ret);
  pos = getLowerBound(x + 1, true);
  resetBuffer();
  buildBuffer(roots[r], roots[l - 1], true, pos, n, 1, n);
  ret += buffer.
}
void program() {
  scanf("%d", &n);
  for (int i = 1, x1, x2, y1, a, b, y2; i <= n; ++i) {
    scanf("%d %d %d %d %d %d", &input[i].x1, &input[i].x2, &input[i].y1, &input[i].a, &input[i].b, &input[i].y2);
    x1s[i] = X(i, input[i].x1);
    x2s[i] = X(i, input[i].x2);
  }
  process();
  int m;
  scanf("%d", &m);
  ll last = 0, x;
  for (int i = 1, l, r; i <= m; ++i) {
    scanf("%d %d %lld", &l, &r, &x);
    x = x + last;
    rollOver(x);
    last = queryAns(l, r, x);
    printf("%lld\n", last);
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
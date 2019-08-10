// AC Persistent Segment Tree
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 5e5
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int input[BUFF(N_MAX)], n;
map<int, int> M;
int RM[BUFF(N_MAX)];
ll ans;
struct N {
  int cnt, l, r;
  N() {}
  N(int l, int r, int cnt) : cnt(cnt), l(l), r(r) {}
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
      int a = buildTree(nodes[prev].l, pos, l, mid);
      int b = buildTree(nodes[prev].r, pos, mid + 1, r);
      nodes[cur] = N(a, b, nodes[a].cnt + nodes[b].cnt);
    }
    return cur;
  }
  return prev;
}
void process() {
  for (auto it = M.begin(); it != M.end(); ++it) {
    roots[it->first] = buildTree(roots[it->first - 1], it->second, 1, n);
    RM[it->second] = it->first;
  }
}
int getKth(int a_ptr, int b_ptr, int k, int l, int r) {
  if (l == r)
    return RM[l];
  int x = nodes[nodes[a_ptr].l].cnt;
  int y = nodes[nodes[b_ptr].l].cnt;
  int cnt = x - y;
  int mid = getMid(l, r);
  if (k <= cnt)
    return getKth(nodes[a_ptr].l, nodes[b_ptr].l, k, l, mid);
  else return getKth(nodes[a_ptr].r, nodes[b_ptr].r, k - cnt, mid + 1, r);
}
void solve(int l, int r) {
  if (l >= r)
    return;
  int len = r - l + 1;
  ans += len;
  int k = (len + 1) / 2;
  int mid = getKth(roots[r], roots[l - 1], k, 1, n);
  solve(l, mid - 1);
  solve(mid + 1, r);
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i]);
    M[input[i]] = i;
  }
  process();
  solve(1, n);
  printf("%lld\n", ans);
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}
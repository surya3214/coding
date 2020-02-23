// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (5e5)
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#define mp make_pair
#define INF (int) 1e9
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef map<int, int> mii;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n;
int in[BUFF(N_MAX)];
struct N {
  int l, r;
  pii val;
  N() {}
  N(int l, int r, pii val) : l(l), r(r), val(val) {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, int val, int idx, int l, int r) {
  if (l <= idx && idx <= r) {
    int cur = ++nodes_ptr;
    if (l == r)
      nodes[cur] = N(0, 0, { val, idx });
    else {
      int mid = getMid(l, r);
      int a = buildTree(nodes[prev].l, val, idx, l, mid);
      int b = buildTree(nodes[prev].r, val, idx, mid + 1, r);
      pii left = (a) ? nodes[a].val : mp(INF, 0);
      pii right = (b) ? nodes[b].val : mp(INF, 0);
      nodes[cur] = N(a, b, min(left, right));
    }
    return cur;
  }
  return prev;
}
pii queryAns(int cur, int sl, int sr, int l, int r) {
  if (!cur || sr < l || r < sl)
    return { INF, 0 };
  if (sl <= l && r <= sr)
    return nodes[cur].val;
  else {
    int mid = getMid(l, r);
    pii x = queryAns(nodes[cur].l, sl, sr, l, mid);
    pii y = queryAns(nodes[cur].r, sl, r, mid + 1, r);
    return min(x, y);
  }
}
void program() {
  cin >> n;
  mii mp;
  for (int i = 1, last_seen; i <= n; ++i) {
    roots[i] = roots[i - 1];
    cin >> in[i];
    last_seen = mp[in[i]] ? mp[in[i]] : -1;
    if (last_seen != -1)
      roots[i] = buildTree(roots[i], INF, last_seen, 1, n);
    roots[i] = buildTree(roots[i], last_seen, i, 1, n);
    mp[in[i]] = i;
  }
  int m;
  cin >> m;
  pii ret;
  for (int i = 1, l, r; i <= m; ++i) {
    cin >> l >> r;
    ret = queryAns(roots[r], l, r, 1, n);
    if (ret.first < l)
      cout << in[ret.second] << endl;
    else cout << "0" << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
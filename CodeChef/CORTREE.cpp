// AC Segment Tree, Pre-order DFS Traversal
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define TREE_SIZE (int) (1 << 18)
#define H_MAX 17
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n, t_time;
vector<int> adj[BUFF(N_MAX)];
pii ranges[BUFF(N_MAX)];
int ancestor[BUFF(N_MAX)][BUFF(H_MAX)];
stack<pair<int, array<int, 2>>> changes;
array<int, 2> st[BUFF(TREE_SIZE)];
void reset() {
  t_time = 0;
}
int getLChild(int x) { return 2 * x; }
int getRChild(int x) { return 2 * x + 1; }
int getMid(int l, int r) { return l + (r - l) / 2; }
void buildAuxiliary(int cur, int l, int r, int &r_m, int &r_l, int &r_r) {
  r_m = getMid(l, r), r_l = getLChild(cur), r_r = getRChild(cur);
}
void updateST(array<int, 2> x, int pos, int cur = 1, int l = 1, int r = n) {
  if (l <= pos && pos <= r) {
    if (l == r)
      st[cur] = x;
    else {
      int mid, left, right;
      buildAuxiliary(cur, l, r, mid, left, right);
      updateST(x, pos, left, l, mid);
      updateST(x, pos, right, mid + 1, r);
      st[cur] = max(st[left], st[right]);
    }
  }
}
void dfs(int u = 1, int p = 0, int depth = 1) {
  int start = ++t_time;
  ancestor[u][0] = p;
  for (int i = 1, half; i <= H_MAX; ++i) {
    half = ancestor[u][i - 1];
    ancestor[u][i] = ancestor[half][i - 1];
  }
  updateST({ depth, u }, start);
  for (auto v: adj[u]) {
    if (v != p)
      dfs(v, u, depth + 1);
  }
  int end = t_time;
  ranges[u] = { start, end };
  adj[u].clear();
}
void removeRange(int sl, int sr, int cur = 1, int l = 1, int r = n) {
  if (sr < l || r < sl)
    return;
  changes.push({ cur, st[cur] });
  if (sl <= l && r <= sr) {
    st[cur] = { 0, 0 };
    return;
  }
  int mid, left, right;
  buildAuxiliary(cur, l, r, mid, left, right);
  removeRange(sl, sr, left, l, mid);
  removeRange(sl, sr, right, mid + 1, r);
  st[cur] = max(st[left], st[right]);
}
int getKthOf(int u, int k) {
  for (int i = H_MAX, rep; u && ~i; --i) {
    rep = (1 << i);
    if (rep & k)
      u = ancestor[u][i];
  }
  return u ? u : 1;
}
void program() {
  reset();
  cin >> n;
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs();
  int ans = 0;
  for (int k = 1; k <= n; ++k) {
    while (1) {
      auto best = st[1];
      if (!best[1])
        break;
      ++ans;
      int idx = getKthOf(best[1], k);
      removeRange(ranges[idx].first, ranges[idx].second);
    }
    while (changes.size()) {
      auto cur = changes.top();
      st[cur.first] = cur.second;
      changes.pop();
    }
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--)
    program();
  return 0;
}
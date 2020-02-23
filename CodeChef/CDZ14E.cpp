// AC PST
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 2e4
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
#define MOD (int) (1e9 + 7)
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n;
pii V[BUFF(N_MAX)];
pii in[BUFF(N_MAX)];
struct N {
  int l, r, cnt;
  ll sum;
  N() {}
  N(int l, int r, int cnt, ll sum) : l(l), r(r), cnt(cnt), sum(sum) {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int buildTree(int prev, ll val, int pos, int l, int r) {
  if (l <= pos && pos <= r) {
    int cur = ++nodes_ptr;
    if (l == r)
      nodes[cur] = N(0, 0, 1, val);
    else {
      int mid = getMid(l, r);
      int a = buildTree(nodes[prev].l, val, pos, l, mid);
      int b = buildTree(nodes[prev].r, val, pos, mid + 1, r);
      nodes[cur] = N(a, b, nodes[a].cnt + nodes[b].cnt,
                    nodes[a].sum + nodes[b].sum);
    }
    return cur;
  }
  return prev;
}
void process() {
  sort(V + 1, V + 1 + n);
  for (int i = 1; i <= n; ++i)
    in[V[i].second].second = i;
  for (int i = 1; i <= n; ++i)
    roots[i] = buildTree(roots[i - 1], in[i].first, in[i].second, 1, n);
}
ll getKSums(int a_ptr, int b_ptr, int& k) {
  if (k == 0 || !nodes[a_ptr].cnt)
    return 0;
  if (nodes[a_ptr].cnt - nodes[b_ptr].cnt <= k) {
    k -= nodes[a_ptr].cnt - nodes[b_ptr].cnt;
    return (nodes[a_ptr].sum - nodes[b_ptr].sum);
  }
  ll x = getKSums(nodes[a_ptr].l, nodes[b_ptr].l, k);
  ll y = getKSums(nodes[a_ptr].r, nodes[b_ptr].r, k);
  return (x + y) % MOD;
}
void program() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> in[i].first;
    V[i] = { in[i].first, i };
  }
  process();
  int m;
  cin >> m;
  for (int i = 1, l, r, k; i <= m; ++i) {
    cin >> l >> r >> k;
    cout << getKSums(roots[r], roots[l - 1], k) << endl;
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
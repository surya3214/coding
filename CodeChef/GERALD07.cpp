// WA
#include <bits/stdc++.h>
#define N_MAX 200010
#define Q_MAX 200010
#define M_MAX 2000010
using namespace std;
int n, m, q, block_size;
int t_ans, t_l, t_r;
struct Q {
  int l, r, idx;
} Query[Q_MAX];
struct E {
  int u, v;
} edges[M_MAX];
int connected[N_MAX], ans[Q_MAX];
bool comparator(Q a, Q b) {
  int a_blk = a.l / block_size;
  int b_blk = b.l / block_size;
  if (a_blk != b_blk)
    return a_blk < b_blk;
  return a.r < b.r;
}
void reset() {
  t_l = t_r = 0;
  t_ans = n;
  for (int i = 1; i <= n; i++)
    connected[i] = 0;
}
void add(int idx) {
  int u, v;
  u = edges[idx].u, v = edges[idx].v;
  if (idx == 0 || (u == v)) return;
  if (connected[u] == 0 || connected[v] == 0)
    t_ans--;
  connected[u]++, connected[v]++;
}
void remove(int idx) {
  int u, v;
  u = edges[idx].u, v = edges[idx].v;
  if (idx == 0 || (u == v)) return;
  connected[u]--, connected[v]--;
  if (connected[u] == 0 || connected[v] == 0)
    t_ans++;
}
void move(int l, int r) {
  if (t_l < l) {
    for (int i = t_l; i < l; i++)
      remove(i);
  }
  if (l < t_l) {
    for (int i = t_l - 1; i >= l; i--)
      add(i);
  }
  if (t_r < r) {
    for (int i = t_r + 1; i <= r; i++)
      add(i);
  }
  if (r < t_r) {
    for (int i = t_r; i > r; i--)
      remove(i);
  }
  t_l = l, t_r = r;
}
void solve() {
  reset();
  for (int i = 1; i <= q; i++) {
    move(Query[i].l , Query[i].r);
    ans[Query[i].idx] = t_ans;
  }
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d %d", &n, &m, &q);
    block_size = ceil(sqrt(n));
    for (int i = 1; i <= m; i++)
      scanf("%d %d", &edges[i].u, &edges[i].v);
    for (int i = 1; i <= q; i++) {
      scanf("%d %d", &Query[i].l, &Query[i].r);
      Query[i].idx = i;
    }
    sort(Query + 1, Query + 1 + q, comparator);
    solve();
    for (int i = 1; i <= q; i++)
      printf("%d\n", ans[i]);
  }
}
int main() {
  program();
  return 0;
}
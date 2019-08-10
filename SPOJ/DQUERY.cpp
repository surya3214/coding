// AC Mo's Algorithm
#include <bits/stdc++.h>
#define N_MAX 30010
#define Q_MAX 200010
#define VAL_MAX 1000010
using namespace std;
int numbers[N_MAX], n, q;
int block_size;
int t_l, t_r, t_ans;
struct Q {
  int l, r, idx;
} Query[Q_MAX];
int ans[Q_MAX], counts[VAL_MAX];
bool comparator(Q a, Q b) {
  int a_blk = a.l / block_size;
  int b_blk = b.l / block_size;
  if (a_blk != b_blk)
    return a_blk < b_blk;
  return a.r < b.r;
}
void add(int idx) {
  int val = numbers[idx];
  if (counts[val] == 0)
    t_ans++;
  counts[val]++;
}
void remove(int idx) {
  int val = numbers[idx];
  counts[val]--;
  if (counts[val] == 0)
    t_ans--;
}
void move(int l, int r) {
  // move t_l to l
  if (t_l < l) {
    for (int i = t_l; i < l; i++)
      remove(i);
  }
  if (l < t_l) {
    for (int i = t_l - 1; i >= l; i--)
      add(i);
  }
  // move t_r to r
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
  t_ans = t_l = t_r = 0;
  for (int i = 1; i <= q; i++) {
    move(Query[i].l, Query[i].r);
    ans[Query[i].idx] = t_ans;
  }
}
void program() {
  scanf("%d", &n);
  block_size = sqrt(n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &numbers[i]);
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    scanf("%d %d", &Query[i].l, &Query[i].r);
    Query[i].idx = i;
  }
  sort(Query + 1, Query + 1 + q, comparator);
  solve();
  for (int i = 1; i <= q; i++)
    printf("%d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
// AC
#include <bits/stdc++.h>
#define Q_MAX 2000010
#define N_MAX 2000010
#define VAL_MAX 2000010
#define block_size 500
using namespace std;
typedef long long int ll;
int n, t, t_l, t_r;
struct Q {
  int l, r, idx;
} Query[Q_MAX];
int numbers[N_MAX];
int counts[VAL_MAX];
ll ans[Q_MAX], t_ans;
bool comparator(Q a, Q b) {
  int blk_a = a.l / block_size;
  int blk_b = b.l / block_size;
  if (blk_a != blk_b)
    return blk_a < blk_b;
  return a.r < b.r;
}
void add(int val) {
  t_ans += (val * (1 + 2 * counts[val]));
  counts[val]++;
}
void subtract(int val) {
  t_ans += (val * (1 - 2 * counts[val]));
  counts[val]--;
}
void solve(int l, int r) {
  // move t_l to l
  if (t_l < l) {
    for (int i = t_l; i < l; i++)
      subtract(numbers[i]);
  }
  if (l < t_l) {
    for (int i = t_l - 1; i >= l; i--)
      add(numbers[i]);
  }
  // move t_r to r
  if (t_r < r) {
    for (int i = t_r + 1; i <= r; i++)
      add(numbers[i]);
  }
  if (r < t_r) {
    for (int i = t_r; i > r; i--)
      subtract(numbers[i]);
  }
  t_l = l, t_r = r;
}
void compute() {
  t_ans = t_l = t_r = 0;
  for (int i = 1; i <= t; i++) {
    solve(Query[i].l, Query[i].r);
    ans[Query[i].idx] = t_ans;
  }
}
void program() {
  scanf("%d %d", &n, &t);
  for (int i = 1; i <= n; i++)
    scanf("%d", &numbers[i]);
  for (int i = 1; i <= t; i++) {
    scanf("%d %d", &Query[i].l, &Query[i].r);
    Query[i].idx = i;
  }
  sort(Query + 1, Query + 1 + t, comparator);
  compute();
  for (int i = 1; i <= t; i++)
    printf("%I64d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
// TLE
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 2500
#define M_MAX 2500
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m, k, diffs_until;
struct {
  int val;
  bool set;
} ans;
struct {
  int beauty[BUFF(M_MAX)];
} flowers[BUFF(N_MAX)];
bool greaterThanAns(int val) {
  if (!ans.set) return false;
  return ans.val <= val;
}
void updateAns(int val) {
  ans.set = true;
  ans.val = val;
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int findLowerBoundInBeauty(int idx, int val) { // returns the right most index x(<= diffs_until) in flowers[idx].beauty[x] <= val
  int l, r, mid;
  l = 1, r = diffs_until;
  while (l <= r) {
    mid = getMid(l, r);
    if (flowers[idx].beauty[mid] <= val)
      l = mid + 1;
    else r = mid - 1;
  }
  return l - 1;
}
void dfs(int idx, int d_l, int d_r) {
  if (greaterThanAns(d_r - d_l)) return;
  if (idx == n + 1) {
    updateAns(d_r - d_l);
    return;
  }
  int l, r, t_l;
  t_l = l = findLowerBoundInBeauty(idx, d_l);
  if (l) {
    r = l + k - 1;
    dfs(idx + 1, min(d_l, flowers[idx].beauty[l]), max(d_r, flowers[idx].beauty[r]));
    ++l, ++r;
    if (l <= diffs_until)
      dfs(idx + 1, min(d_l, flowers[idx].beauty[l]), max(d_r, flowers[idx].beauty[r]));
  }
  l = findLowerBoundInBeauty(idx, d_r);
  if (t_l != l && l) {
    r = l + k - 1;
    dfs(idx + 1, min(d_l, flowers[idx].beauty[l]), max(d_r, flowers[idx].beauty[r]));
    --l, --r;
    if (l && l <= diffs_until)
      dfs(idx + 1, min(d_l, flowers[idx].beauty[l]), max(d_r, flowers[idx].beauty[r]));
  }
}
struct Q {
  int l, r, val;
} queries[BUFF(N_MAX)];
int q_ptr;
bool m_comparator(Q a, Q b) {
  if (a.val != b.val) return a.val < b.val;
  return a.l < b.l;
}
void compute() {
  int r;
  for (int l = 1; l <= diffs_until; ++l) {
    ++q_ptr;
    r = l + k - 1;
    queries[q_ptr].l = flowers[1].beauty[l];
    queries[q_ptr].r = flowers[1].beauty[r];
    queries[q_ptr].val = flowers[1].beauty[r] - flowers[1].beauty[l];
  }
  sort(queries + 1, queries + 1 + q_ptr, m_comparator);
  for (int i = 1; i <= q_ptr; ++i)
    dfs(2, queries[i].l, queries[i].r);
}
void program() {
  ll x;
  int a, b, c, l, r;
  scanf("%d %d %d", &n, &m, &k);
  diffs_until = m - k + 1;
  for (int i = 1; i <= n; ++i) {
    scanf("%lld %d %d %d", &x, &a, &b, &c);
    for (int j = 1; j <= m; ++j) {
      flowers[i].beauty[j] = x;
      x = (a * x + b) % c;
    }
    sort(flowers[i].beauty + 1, flowers[i].beauty + 1 + m);
  }
  compute();
  printf("%d\n", ans.val);
}
int main() {
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}
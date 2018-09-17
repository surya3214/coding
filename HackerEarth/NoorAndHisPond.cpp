// AC Kinda Scheduling
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  int s, e;
} fish[BUFF(N_MAX)];
struct D {
  bool type;
  int val;
  int idx;
} d_vals[BUFF(2 * N_MAX)];
int d_ptr, base_val;
int cnt[BUFF(2 * N_MAX)];
int n, ans;
void reset() {
  for (int i = 1; i <= base_val; ++i)
    cnt[i] = 0;
  ans = d_ptr = 0;
}
void addDVal(int x, bool type, int idx) {
  ++d_ptr;
  d_vals[d_ptr].val = x;
  d_vals[d_ptr].type = type;
  d_vals[d_ptr].idx = idx;
}
bool d_comparator(D a, D b) { return a.val < b.val; }
void compress() {
  base_val = 0;
  int l, r;
  l = 1;
  while (l <= d_ptr) {
    ++base_val;
    r = l;
    while (r + 1 <= d_ptr && d_vals[r + 1].val == d_vals[r].val)
      ++r;
    for (int i = l; i <= r; ++i)
      if (d_vals[i].type)
        fish[d_vals[i].idx].s = base_val;
      else fish[d_vals[i].idx].e = base_val;
    l = r + 1;
  }
}
void compute() {
  int x;
  for (int i = 1; i <= n; ++i) {
    ++cnt[fish[i].s];
    --cnt[fish[i].e];
  }
  x = 0;
  for (int i = 1; i <= base_val; ++i) {
    x += cnt[i];
    ans = max(ans, x);
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d", &fish[i].e, &fish[i].s);
      addDVal(fish[i].s, true, i);
      addDVal(fish[i].e, false, i);
    }
    sort(d_vals + 1, d_vals + 1 + d_ptr, d_comparator);
    compress();
    compute();
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
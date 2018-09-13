// AC Prefix Sum
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct {
  int l, r;
  int time;
} ans[BUFF(N_MAX)];
struct {
  int val;
  int time;
} cnt[BUFF(N_MAX)];
int t_time;
void reset() {
  ++t_time;
}
void sanitizeCnt(int x) {
  if (cnt[x].time != t_time) {
    cnt[x].val = 0;
    cnt[x].time = t_time;
  }
}
void updateAns(int x, int l, int r) {
  if (ans[x].time != t_time || ans[x].r - ans[x].l < r - l) {
    ans[x].l = l;
    ans[x].r = r;
    ans[x].time = t_time;
  }
}
void program() {
  int tcase, q, l, r, x, t_r;
  struct {
    int idx;
    int val;
  } last_seen;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d", &n, &q);
    t_r = n;
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d", &l, &r);
      sanitizeCnt(l);
      sanitizeCnt(r);
      ++cnt[l].val;
      --cnt[r].val;
      t_r = max(t_r, r);
    }
    x = last_seen.val = 0;
    for (int i = 1; i <= t_r; ++i) {
      sanitizeCnt(i);
      x += cnt[i].val;
      if (last_seen.val != x) {
        last_seen.val = x;
        last_seen.idx = i;
      }
      updateAns(x, last_seen.idx, i);
    }
    printf("Case %d:\n", t);
    for (int i = 1; i <= q; ++i) {
      scanf("%d", &x);
      if (ans[x].time == t_time)
        printf("%d %d\n", ans[x].l, ans[x].r);
      else printf("-1\n");
    }
  }
}
int main() {
  program();
  return 0;
}
// AC 0.00 F yeah!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, t_time;
int candy[BUFF(N_MAX)];
struct C {
  int idx;
  int val;
} sorted_candy[BUFF(N_MAX)];
int t_next[BUFF(N_MAX)];
int cnt[BUFF(N_MAX)];
struct {
  int time;
  int val;
} dp[BUFF(N_MAX)][BUFF(N_MAX)];
void sanitizeDP(int l, int r) {
  if (dp[l][r].time != t_time) {
    dp[l][r].val = -1;
    dp[l][r].time = t_time;
  }
}
int compute(int l, int r) {
  if (l == r) return 1;
  else if (l > r) return 0;
  sanitizeDP(l, r);
  if (dp[l][r].val != -1)
    return dp[l][r].val;
  int ret = 0;
  int idx = l;
  int seen = 1;
  while (t_next[idx] != -1) {
    ret = max(ret, cnt[seen] + compute(idx + 1, r));
    idx = t_next[idx];
    ++seen;
  }
  ret = max(ret, cnt[seen] + compute(idx + 1, r));
  return dp[l][r].val = ret;
}
bool m_comparator(C a, C b) {
  if (a.val != b.val)
    return a.val < b.val;
  return a.idx < b.idx;
}
void reset() { ++t_time; }
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &candy[i]);
      sorted_candy[i].val = candy[i];
      sorted_candy[i].idx = i;
    }
    sort(sorted_candy + 1, sorted_candy + 1 + n, m_comparator);
    sorted_candy[n + 1].val = -1;
    for (int i = 1; i <= n; ++i) {
      if (sorted_candy[i + 1].val == sorted_candy[i].val)
        t_next[sorted_candy[i].idx] = sorted_candy[i + 1].idx;
      else t_next[sorted_candy[i].idx] = -1;
    }
    printf("%d\n", compute(1, n));
  }
}
void ready() {
  for (int i = 1; i <= N_MAX; ++i)
    cnt[i] = i + cnt[i - 1];
}
int main() {
  ready();
  program();
  return 0;
}
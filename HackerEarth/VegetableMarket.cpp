// AC Implementation
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX (int) 1e6
#define Q_MAX (int) 1e5
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, q;
int seen[BUFF(VAL_MAX)];
ll sum[BUFF(VAL_MAX)];
int ans[BUFF(Q_MAX)];
int cursor_at;
int max_v;
struct Q {
  ll sum;
  int idx;
} queries[BUFF(Q_MAX)];
bool q_comparator(Q a, Q b) { return a.sum < b.sum; }
void moveCursor(ll x) {
  while (cursor_at <= max_v && sum[cursor_at] < x)
    ++cursor_at;
}
void compute() {
  int higher_cnt = n;
  ll sum_so_far = 0;
  for (int i = 1; i <= max_v; ++i) {
    sum[i] = sum_so_far + (1LL * i * higher_cnt);
    higher_cnt -= seen[i];
    sum_so_far += (1LL * seen[i] * i);
  }
  for (int i = 1; i <= q; ++i) {
    if (sum[max_v] < queries[i].sum)
      ans[queries[i].idx] = -1;
    else {
      moveCursor(queries[i].sum);
      ans[queries[i].idx] = cursor_at;
    }
  }
}
void program() {
  int x;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    ++seen[x];
    max_v = max(max_v, x);
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &queries[i].sum);
    queries[i].idx = i;
  }
  sort(queries + 1, queries + 1 + q, q_comparator);
  compute();
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
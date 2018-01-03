//
#include <bits/stdc++.h>
#define N_MAX 100010
#define M_MAX 100010
using namespace std;
int numbers[N_MAX];
int n, l, r, ans;
struct {
  int last_seen[M_MAX];
  int last_seen_time[M_MAX];
  int cur_time;
} lazyMap;
void reset() {
  lazyMap.cur_time++;
  ans = 0;
}
void update(int idx) {
  int val = numbers[idx];
  if (lazyMap.last_seen_time[val] == lazyMap.cur_time)
    ans = max(ans, idx - lazyMap.last_seen[val]);
  else lazyMap.last_seen[val] = idx, lazyMap.last_seen_time[val] = lazyMap.cur_time;
}
void solve() {
  reset();
  for (int i = l; i <= r; i++) {
    update(i);
  }
}
void program() {
  int m, k, q;
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; i++)
    scanf("%d", &numbers[i]);
  for (int i = 1; i <= q; i++) {
    scanf("%d %d", &l, &r);
    solve();
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
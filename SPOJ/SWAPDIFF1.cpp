// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n, t_time;
ll ans;
int input[BUFF(N_MAX)];
struct {
  int time;
  int val;
} BIT[BUFF(N_MAX)];
void reset() {
  ++t_time;
  ans = 0;
}
void sanitizeBIT(int idx) {
  if (BIT[idx].time != t_time) {
    BIT[idx].val = 0;
    BIT[idx].time = t_time;
  }
}
void addToBIT(int idx) {
  while (idx <= n) {
    sanitizeBIT(idx);
    ++BIT[idx].val;
    idx = idx + (idx & -idx);
  }
}
int getBIT(int idx) {
  int ret = 0;
  while (idx > 0) {
    sanitizeBIT(idx);
    ret += BIT[idx].val;
    idx = idx - (idx & -idx);
  }
  return ret;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &input[i]);
    for (int i = 1; i <= n; ++i) {
      ans += i - 1 - getBIT(input[i]);
      addToBIT(input[i]);
    }
    printf("%lld\n", ans);
  }
}
int main() {
  program();
  return 0;
}
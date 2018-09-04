// AC BIT
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 200000
#define VAL_MAX (int) 1e7
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
ll ans;
int numbers[BUFF(N_MAX)];
struct {
  int time;
  int cnt;
} BIT[BUFF(VAL_MAX)];
int t_time;
void reset() {
  ++t_time;
  ans = 0;
}
void sanitizeBIT(int x) {
  if (BIT[x].time != t_time) {
    BIT[x].cnt = 0;
    BIT[x].time = t_time;
  }
}
void addToBIT(int x) {
  while (x <= VAL_MAX) {
    sanitizeBIT(x);
    ++BIT[x].cnt;
    x = x + (x & -x);
  }
}
int queryBIT(int x) {
  int cnt = 0;
  while (x) {
    sanitizeBIT(x);
    cnt += BIT[x].cnt;
    x = x - (x & -x);
  }
  return cnt;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &numbers[i]);
    for (int i = n; i >= 1; --i) {
      ans += queryBIT(numbers[i] - 1);
      addToBIT(numbers[i]);
    }
    printf("%lld\n", ans);
  }
}
int main() {
  program();
  return 0;
}
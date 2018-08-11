// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 10000
#define VAL_MAX 1000000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n, ans, t_time;
int input[BUFF(N_MAX)];
struct{
  int time;
  int count;
} seen[BUFF(VAL_MAX)];
void reset() {
  ++t_time;
  ans = 0;
}
void sanitizeSeen(int idx) {
  if (seen[idx].time != t_time) {
    seen[idx].count = 0;
    seen[idx].time = t_time;
  }
}
void addSeenCount(int x) { sanitizeSeen(x); ++seen[x].count; }
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &input[i]);
      addSeenCount(input[i]);
    }
    for (int i = 1; i <= n; ++i) {
      for (ll p = 1; p <= VAL_MAX; p *= input[i]) {
        sanitizeSeen(p);
        if ((p == input[i] && seen[p].count > 1) || (p != input[i] && seen[p].count)) {
          ++ans;
          break;
        }
        if (input[i] == 1) break;
      }
    }
    printf("Case %d: %d\n", t, ans);
  }
}
int main() {
  program();
  return 0;
}
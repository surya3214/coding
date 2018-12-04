// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m, x, ans;
int a[BUFF(N_MAX)], b[BUFF(N_MAX)];
void reset() { ans = 0; }
void solve() {
  int left = x;
  int a_ptr, b_ptr;
  for (a_ptr = 1; a_ptr <= n; ++a_ptr) {
    if (left >= a[a_ptr])
      left -= a[a_ptr];
    else break;
  }
  ans = --a_ptr;
  for (b_ptr = 1; b_ptr <= m; ++b_ptr) {
    if (left < b[b_ptr]) {
      while (a_ptr >= 1 && left < b[b_ptr]) {
        left += a[a_ptr];
        --a_ptr;
      }
    }
    if (left >= b[b_ptr]) {
      left -= b[b_ptr];
      ans = max(ans, a_ptr + b_ptr);
    } else break;
  }
}
void program() {
  int g;
  scanf("%d", &g);
  for (int t = 1; t <= g; ++t) {
    reset();
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i)
      scanf("%d", &b[i]);
    solve();
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
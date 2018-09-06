// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, k, l, r, last_non_zero_at;
ll prod, cnt;
int inp[BUFF(N_MAX)];
int last_n_zeros[BUFF(N_MAX)];
void reset() {
  l = 1, r = 0;
  cnt = last_non_zero_at = 0;
  prod = 1;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &inp[i]);
      if (inp[i] != 1)
        last_non_zero_at = i;
      last_n_zeros[i] = last_non_zero_at;
    }
    reset();
    while (l <= n) {
      while (r + 1 <= n && prod * inp[r + 1] <= k) {
        prod = prod * inp[r + 1];
        ++r;
      }
      if (prod == k)
        cnt += r - max(l, last_n_zeros[r]) + 1;
      prod = prod / inp[l];
      ++l;
    }
    printf("%lld\n", cnt);
  }
}
int main() {
  program();
  return 0;
}
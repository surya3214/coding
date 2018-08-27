// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
ll inp[BUFF(N_MAX)];
ll p_sum[BUFF(N_MAX)];
ll sum_so_far;
void program() {
  int q, l, r;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &inp[i]);
    sum_so_far += inp[i];
    p_sum[i] = p_sum[i - 1] + (inp[i] * sum_so_far);
    inp[i] += inp[i - 1];
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &l, &r);
    ++l; ++r;
    printf("%lld\n", (p_sum[r] - p_sum[l - 1]) - (inp[r] - inp[l - 1]) * inp[l - 1]);
  }
}
int main() {
  program();
  return 0;
}
// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (1e7)
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
ll ans;
ll nums[BUFF(N_MAX)];
void compute() {
  ll x = 0;
  for (int i = 1; i <= n; ++i) {
    x += nums[i];
    ans = max(ans, x);
  }
}
void program() {
  int m, l, r, k;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d %d", &l, &r, &k);
    nums[l] += k;
    nums[r + 1] -= k;
  }
  compute();
  printf("%lld\n", ans);
}
int main() {
  program();
  return 0;
}
// AC
#include <iostream>
#include <cstdio>
#define K_MAX 100010
#define N_MAX 100010
#define MOD 1000000007
using namespace std;
typedef long long int ll;
int n, k, x;
int dp[N_MAX]; // number of ways we can fill A[1, i] and A[i] != 1
int mod(ll x) {
  while (x < 0)
    x += MOD;
  return x % MOD;
}
int fermats(int x, int y) {
  // calculate x ^ y;
  if (!y)
    return 1;
  int product = fermats(x, y / 2);
  product = mod(product * 1LL * product);
  if (y & 1)
    product = mod(product * 1LL * x);
  return product;
}
void solve() {
  dp[0] = 1;
  for (int i = 2; i <= n; i++)
    dp[i] = mod(mod(1LL * (k - 1) * dp[i - 2]) + mod(1LL * (k - 2) * dp[i - 1]));
}
void program() {
  scanf("%d %d %d", &n, &k, &x);
  solve();
  if (x == 1)
    printf("%d\n", dp[n - 1]);
  else printf("%d\n", mod(dp[n] * 1LL * fermats(k - 1, MOD - 2)));
}
int main() {
  program();
  return 0;
}
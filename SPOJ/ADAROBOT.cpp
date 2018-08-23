// AC
#include <stdio.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e8
#define Q_MAX (int) 1e6
#define BITS_MAX 32
#pragma GCC optimize "O4"
typedef long long int ll;
typedef unsigned long long int ull;
ll dp[BUFF(N_MAX)];
int cubes[BUFF(BITS_MAX)];
struct {
  int n;
} queries[BUFF(Q_MAX)];
void preprocess(int n) {
  for (int i = 1; i <= 31; ++i)
    cubes[i] = i * i * i;
  for (int i = 1; i <= n; ++i)
    dp[i] = cubes[__builtin_ffs(i << 1)] + dp[i - 1];
}
int max_n;
int max(int a, int b) { return a > b ? a : b; }
void program() {
  int q, n;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &queries[i].n);
    max_n = max(max_n, queries[i].n);
  }
  preprocess(max_n >> 1);
  for (int i = 1; i <= q; ++i)
    printf("%lld\n", dp[queries[i].n >> 1]);
}
int main() {
  program();
  return 0;
}
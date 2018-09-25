// AC Implementation
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
ll rev_count;
ll a[BUFF(N_MAX)], b[BUFF(N_MAX)];
void compute() {
  ll rev_needed;
  for (int i = n; i; --i) {
    a[i] += rev_count;
    if (a[i] % b[i] != 0) {
      rev_needed = b[i] * (a[i] / b[i] + 1);
      rev_count += rev_needed - a[i];
    }
  }
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld %lld", &a[i], &b[i]);
  compute();
  printf("%lld\n", rev_count);
}
int main() {
  program();
  return 0;
}
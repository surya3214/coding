// AC Simulation Adhoc
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, k;
ll b[BUFF(N_MAX)];
void program() {
  int x, ans;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    b[i] = x - (1LL * (i - 1) * k);
  }
  sort(b + 1, b + 1 + n);
  int l, r;
  l = 1;
  ans = n;
  while (l <= n) {
    r = l;
    while (r + 1 <= n && b[r] == b[r + 1])
      ++r;
    ans = min(ans, n - (r - l + 1));
    l = r + 1;
  }
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
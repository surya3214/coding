// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
ll numbers[BUFF(N_MAX)];
int n, l;
ll m, sum, ans;
void reset() { sum = ans = l = 0; }
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", &numbers[i]);
      numbers[i] %= m;
      sum += numbers[i];
      while (sum >= m)
        sum -= numbers[l++];
      ans = max(ans, sum);
    }
    printf("%lld\n", ans);
  }
}
int main() {
  program();
  return 0;
}
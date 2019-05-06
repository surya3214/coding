// AC Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX (int) (2 * 1e4)
#define N_MAX (int) 1e4
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int cnt[BUFF(VAL_MAX)];
int numbers[BUFF(N_MAX)];
void program() {
  int n, d, ans;
  scanf("%d %d", &n, &d);
  ans = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &numbers[i]);
    ++cnt[numbers[i]];
  }
  for (int i = 1; i <= n; ++i) {
    if (numbers[i] + (2 * d) <= VAL_MAX)
      ans += (cnt[numbers[i] + d] * cnt[numbers[i] + (2 * d)]);
  }
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
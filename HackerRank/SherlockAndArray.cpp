// AC Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (1e5)
#pragma GCC optimize "O0"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int l_sum, r_sum;
int num[BUFF(N_MAX)];
void program() {
  int tcase, n;
  bool ans;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d", &n);
    l_sum = r_sum = 0;
    ans = false;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &num[i]);
      r_sum += num[i];
    }
    for (int i = 1; i <= n && !ans; ++i) {
      if (l_sum == r_sum - num[i])
        ans = true;
      else {
        l_sum += num[i];
        r_sum -= num[i];
      }
    }
    if (ans)
      printf("YES\n");
    else printf("NO\n");
  }
}
int main() {
  program();
  return 0;
}
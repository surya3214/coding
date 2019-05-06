// AC Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX (int) 1e5
#define INF 1e9
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int last_seen[BUFF(VAL_MAX)];
void program() {
  int n, x, ans;
  scanf("%d", &n);
  ans = INF;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    if (last_seen[x])
      ans = min(ans, i - last_seen[x]);
    last_seen[x] = i;
  }
  if (ans == INF)
    ans = -1;
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
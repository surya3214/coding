// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, l, r;
int cakes[BUFF(N_MAX)];
struct {
  int cnt;
  int max_h;
} ans;
void reset() {
  l = 1;
  ans.cnt = 0;
  ans.max_h = 0;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &cakes[i]);
    sort(cakes + 1, cakes + 1 + n);
    while (l <= n) {
      r = l;
      ++ans.cnt;
      while (r + 1 <= n && cakes[r + 1] == cakes[r])
        ++r;
      ans.max_h = max(ans.max_h, r - l + 1);
      l = r + 1;
    }
    printf("%d %d\n", ans.cnt, ans.max_h);
  }
}
int main() {
  program();
  return 0;
}
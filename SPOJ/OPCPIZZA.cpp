// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int inp[BUFF(N_MAX)];
int cnt[BUFF(N_MAX)];
int n, k;
int getMid(int l, int r) { return l + (r - l) / 2; }
int findBS(int l, int r, int x) {
  int mid;
  while (l <= r) {
    mid = getMid(l, r);
    if (inp[mid] <= x)
      l = mid + 1;
    else r = mid - 1;
  }
  return l - 1;
}
void program() {
  int tcase, q, ans;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    ans = 0, q = 2;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &inp[i]);
    sort(inp + 1, inp + 1 + n);
    for (int i = 1; i <= n; ++i)
      if (inp[i] == inp[i - 1])
        cnt[i] = 1 + cnt[i - 1];
      else cnt[i] = 1;
    for (int i = 1; i <= n; ++i) {
      q = findBS(i + 1, n, k - inp[i]);
      if (i != q && inp[i] + inp[q] == k)
        ++ans;
    }
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
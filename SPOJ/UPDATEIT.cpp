// AC Prefix Sum
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 10000
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int cnt[BUFF(N_MAX)];
int n;
void reset() { memset(cnt, 0, sizeof(cnt)); }
void program() {
  int tcase, q, l, r, x;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= q; ++i) {
      scanf("%d %d %d", &l, &r, &x);
      cnt[l] += x;
      cnt[r + 1] -= x;
    }
    x = 0;
    for (int i = 0; i <= n; ++i) {
      x += cnt[i];
      cnt[i] = x;
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
      scanf("%d", &x);
      printf("%d\n", cnt[x]);
    }
  }
}
int main() {
  program();
  return 0;
}
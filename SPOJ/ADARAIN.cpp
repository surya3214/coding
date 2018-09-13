// AC Prefix Sum
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define W_MAX 1000000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int w;
int cnt[BUFF(W_MAX)];
void program() {
  int n, m;
  scanf("%d %d %d", &n, &m, &w);
  int l, r;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &l, &r);
    ++cnt[l];
    --cnt[r + 1];
  }
  int x = 0;
  for (int i = 0; i <= w; ++i) {
    x = x + cnt[i];
    cnt[i] = x;
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &x);
    printf("%d\n", cnt[x]);
  }
}
int main() {
  program();
  return 0;
}
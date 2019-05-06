// AC Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
void program() {
  int s, t, a, b, m, n, pos;
  int apples, oranges;
  apples = oranges = 0;
  scanf("%d %d %d %d %d %d", &s, &t, &a, &b, &m, &n);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &pos);
    pos += a;
    if (pos >= s && pos <= t)
      ++apples;
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &pos);
    pos += b;
    if (pos >= s && pos <= t)
      ++oranges;
  }
  printf("%d\n%d\n", apples, oranges);
}
int main() {
  program();
  return 0;
}
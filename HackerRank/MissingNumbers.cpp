// AC Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX (int) (1e4)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int freq[BUFF(VAL_MAX)];
void program() {
  int n, m, x;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    ++freq[x];
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &x);
    --freq[x];
  }
  for (int i = 1; i <= VAL_MAX; ++i)
    if (freq[i] != 0)
      printf("%d ", i);
}
int main() {
  program();
  return 0;
}
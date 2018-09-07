// AC Z Algorithm
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
ll cnt;
int Z[BUFF(LEN_MAX)];
void buildZ() {
  cnt = 0;
  int l, r, k;
  l = r = 0;
  for (int i = 1; ; ++i) {
    if (!str[i]) {
      cnt += i;
      break;
    }
    if (i > r) {
      l = r = i;
      while (str[r] && str[r] == str[r - l])
        ++r;
      Z[i] = r - l;
      --r;
    } else {
      k = i - l;
      if (Z[k] < r - i + 1)
        Z[i] = Z[k];
      else {
        l = i;
        while (str[r] && str[r] == str[r - l])
          ++r;
        Z[i] = r - l;
        --r;
      }
    }
    cnt += Z[i];
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%s", str);
    buildZ();
    printf("%lld\n", cnt);
  }
}
int main() {
  program();
  return 0;
}
// AC Ad hoc
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
void program() {
  int tcase;
  int a, b, k;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d %d", &a, &b, &k);
    printf("Case %d: ", t);
    if (k != 0 && b + k == a)
      printf("YES\n");
    else printf("NO\n");
  }
}
int main() {
  program();
  return 0;
}
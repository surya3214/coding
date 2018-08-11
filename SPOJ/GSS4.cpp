// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX 1e18
#define ARRAY_SIZE_MAX (int) 1e8
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
ll sqrt_map[BUFF(ARRAY_SIZE_MAX)];
void getSquareRootOf(ll val) {
  ll i = 1e8;
  ll times = 0;
  while (i * i <= val) ++i, ++times;
  printf("%lld\n", times);
}
void program() {
  getSquareRootOf(VAL_MAX);
}
int main() {
  program();
  return 0;
}
// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
bool isPrime(ll x) {
  for (ll i = 2; i * i <= x; ++i)
    if (x % i == 0) return false;
  return true;
}
void program() {
  int tcase, x;
  ll l, r;
  scanf("%d", &tcase);
  for (int t = 1;  t <= tcase; ++t) {
    scanf("%lld %lld", &l, &r);
    if (l <= 2) printf("2\n"), l = 3;
    if (!(l & 1)) ++l;
    for (ll i = l; i <= r; i += 2)
      if (isPrime(i)) printf("%lld\n", i);
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}
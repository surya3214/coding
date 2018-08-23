// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
bool isPrime(int x) {
  if (x < 2) return false;
  for (int i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return true;
}
void program() {
  int l, r;
  scanf("%d %d", &l, &r);
  ull sum = 0;
  while (r > l) {
    sum += r;
    if (isPrime(r)) break;
    --r;
  }
  printf("%lld\n", sum);
}
int main() {
  program();
  return 0;
}
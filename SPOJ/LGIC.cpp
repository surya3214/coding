// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
ll compute(int n) {
  if (n <= 2) return n * 2;
  ll fact, ret, diff;
  diff = fact = 2;
  int counter = 1;
  for (int i = 3; i <= n; ++i) {
    fact *= i;
    diff = 2 * diff + counter;
    ret = fact + diff;
    ++counter;
  }
  return ret;
}
void program() {
  int n;
  scanf("%d", &n);
  printf("%lld\n", compute(n));
}
int main() {
  program();
  return 0;
}
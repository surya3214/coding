// AC Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
bool isKeplar(int x) {
  ll square = 1LL * x * x;
  int digits, y;
  digits = 0;
  y = x;
  while (y) {
    ++digits;
    y = y / 10;
  }
  for (int i = 1; i <= digits; ++i) {
    y += (pow(10, (i - 1)) * (square % 10));
    square /= 10;
  }
  return (square + y) == x;
}
void program() {
  int l, r;
  scanf("%d %d", &l, &r);
  bool found = false;
  for (int i = l; i <= r; ++i) {
    if (isKeplar(i)) {
      printf("%d ", i);
      found = true;
    }
  }
  if (!found)
    printf("INVALID RANGE");
}
int main() {
  program();
  return 0;
}
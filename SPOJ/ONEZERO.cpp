//
#include <iostream>
#include <cstdio>
#define N_MAX 20010
using namespace std;
int n;
int ans[N_MAX];
bool findProduct(int n, int carry) {
  int digit = n % 10, result, pos;
  if (n == 0) {
    if (carry == 1) {
      pos = ++ans[0];
      ans[pos] = carry;
      return true;
    } else if (carry == 0)
      return true;
    else return false;
  }
  for (int i = 1; i <= 9; i++) {
    result = digit * i + carry;
    if ((result % 10) == 1 || (result % 10) == 0) {
      pos = ++ans[0];
      ans[pos] = result % 10;
      if (findProduct(n / 10, result / 10))
        return true;
      // backtrack
      --ans[0];
    }
  }
  return false;
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    ans[0] = 0;
    scanf("%d", &n);
    findProduct(n, 0);
    for (int i = ans[0]; i > 0; i--)
      printf("%d", ans[i]);
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}
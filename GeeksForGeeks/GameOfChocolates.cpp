//
#include <iostream>
#include <cstdio>
using namespace std;
void program() {
  int tcase, a, b, grundy_a, grundy_b, ans;
  scanf("%d", &tcase);
  while (tcase--) {
    scanf("%d %d", &a, &b);
    grundy_a = a;
    grundy_b = b;
    if (a > b)
      grundy_a = b;
    else grundy_b = a;
    
  }
}
int main() {
  program();
  return 0;
}
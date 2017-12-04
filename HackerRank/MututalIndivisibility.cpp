// HR AC
#include <iostream>
#include <stdio.h>
using namespace std;
void program() {
  int t, a, b, x, k;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d %d", &a, &b, &x);
    k = min(b - a + 1, (b + 1) / 2);
    if (k < x)
      printf("-1");
    else {
      for (int i = 0; i < x; i++)
        printf("%d ", b - i);
    }
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}
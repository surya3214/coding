//
#include <iostream>
#include <cstdio>
using namespace std;
void program() {
  int q, n, k, x, d, t;
  int upfront, fee;
  scanf("%d", &q);
  while (q--) {
    upfront = fee = 0;
    scanf("%d %d %d %d", &n, &k, &x, &d);
    upfront = d;
    for (int i = 0; i < n; i++) {
      scanf("%d", &t);
      fee += max(k, t * x / 100);
    }
    if (upfront < fee)
      printf("upfront\n");
    else printf("fee\n");
  }
}
int main() {
  // freopen("BankAccounts_input.txt", "r", stdin);
  program();
  return 0;
}
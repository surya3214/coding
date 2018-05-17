// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
using namespace std;
int elements[BUFF(N_MAX)];
int n;
int ans;
int gcd(int a, int b) {
  if (a == 0) return b;
  return gcd(b % a, a);
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  while (tcase--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &elements[i]);
      if (i == 1) ans = elements[i];
      else ans = gcd(ans, elements[i]);
    }
    if (ans == 1) ans = 0;
    else ans = -1;
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
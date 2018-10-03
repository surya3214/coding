// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int t_swap(int &a, int &b) {
  if (b < a) {
    int t = b;
    b = a;
    a = t;
  }
}
struct {
  ll pos;
  ll neg;
} ans;
ll compute(int x) { return (1LL * x * (x + 1)) / 2; }
void program() {
  int a, b;
  while (scanf("%d %d", &a, &b) != EOF) {
    t_swap(a, b);
    ans.pos = ans.neg = 0;
    if (a < 0)
      ans.neg = compute(-a);
    else ans.pos = -compute(a - 1);
    if (b < 0)
      ans.neg -= compute(-b - 1);
    else ans.pos += compute(b);
    printf("%lld\n", ans.pos - ans.neg);
  }
}
int main() {
  program();
  return 0;
}
// AC Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  int cnt;
  int val;
} tallest;
void program() {
  int n, x;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    if (x > tallest.val) {
      tallest.val = x;
      tallest.cnt = 1;
    } else if (x == tallest.val)
      ++tallest.cnt;
  }
  printf("%d\n", tallest.cnt);
}
int main() {
  program();
  return 0;
}
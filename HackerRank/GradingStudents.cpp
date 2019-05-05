// AC Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
void process() {
  if (n < 38)
    return;
  int x = n % 10;
  switch (x) {
    case 3:
    case 8: n += 2; break;
    case 4:
    case 9: ++n; break;
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d", &n);
    process();
    printf("%d\n", n);
  }
}
int main() {
  program();
  return 0;
}
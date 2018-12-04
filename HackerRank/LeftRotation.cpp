// AC Implementation
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int numbers[BUFF(N_MAX)];
void program() {
  int n, d, x;
  scanf("%d %d", &n, &d);
  for (int i = 1; i <= n; ++i) {
    x = i - d;
    if (x <= 0)
      x += n;
    scanf("%d", &numbers[x]);
  }
  for (int i = 1; i <= n; ++i)
    printf("%d ", numbers[i]);
}
int main() {
  program();
  return 0;
}
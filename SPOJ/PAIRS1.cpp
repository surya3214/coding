// AC
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
  int n, k, l, r;
  ll diff, cnt;
  cnt = 0;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &numbers[i]);
  sort(numbers + 1, numbers + 1 + n);
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (numbers[j] - numbers[i] == k) ++cnt;
      else if (numbers[j] - numbers[i] > k) break;
    }
  }
  printf("%lld\n", cnt);
}
int main() {
  program();
  return 0;
}
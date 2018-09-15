// AC Two Pointers
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, k;
int numbers[BUFF(N_MAX)];
void program() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &numbers[i]);
  sort(numbers + 1, numbers + 1 + n);
  int r = 1, width = 1, cnt = 0;
  for (int i = 1; i <= n; ++i) {
    while (r + 1 <= n && numbers[r + 1] - numbers[i] <= k) {
      if (numbers[r + 1] == numbers[r])
        ++width;
      else width = 1;
      ++r;
    }
    if (numbers[r] - numbers[i] == k)
      cnt += width;
  }
  printf("%d\n", cnt);
}
int main() {
  program();
  return 0;
}
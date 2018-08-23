// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int inp[BUFF(N_MAX)];
int cnt[BUFF(N_MAX)];
int n, k, ans;
void program() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &inp[i]);
  sort (inp + 1, inp + 1 + n);
  for (int i = 1; i <= n; ++i)
    if (inp[i] == inp[i - 1])
      cnt[i] = 1 + cnt[i - 1];
    else cnt[i] = 1;
  int t = 1;
  for (int i = 1; i <= n; ++i) {
    if (inp[n] - inp[i] < k) break;
    while (t + 1 <= n && inp[t + 1] <= inp[i] + k)
      ++t;
    if (inp[t] == inp[i] + k)
      ans += cnt[t];
  }
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 10000
using namespace std;
typedef long long int ll;
ll prefix_sum[BUFF(N_MAX)];
ll t_array[BUFF(N_MAX)];
int n;
void program() {
  int tcase;
  ll diff;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    diff = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", &t_array[i]);
      prefix_sum[i] = t_array[i] + prefix_sum[i - 1];
    }
    for (int i = 1; i < n; ++i)
      diff += (prefix_sum[n] - prefix_sum[i]) - (t_array[i] * (n - i));
    printf("%lld\n", diff);
  }
}
int main() {
  program();
  return 0;
}
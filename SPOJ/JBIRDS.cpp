// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 10000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n;
int parrots[BUFF(N_MAX)];
int l_sum, r_sum;
int m_abs(int x) { return x > 0 ? x : -x; }
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &parrots[i]);
  sort(parrots + 1, parrots + 1 + n);
  l_sum = r_sum = 0;
  if (n >= 1) l_sum = parrots[n];
  for (int i = n - 1; i >= 1; --i) {
    if (l_sum < r_sum) l_sum += parrots[i];
    else r_sum += parrots[i];
  }
  printf("%d\n", m_abs(r_sum - l_sum));
}
int main() {
  program();
  return 0;
}
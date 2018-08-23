// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
bitset<BUFF(VAL_MAX)> m_set[2];
int total[BUFF(VAL_MAX)];
void program() {
  int n, q, t, l, r;
  scanf("%d %d", &n, &q);
  bool cur;
  m_set[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    cur = i & 1;
    m_set[cur] = m_set[!cur] | (m_set[!cur] << t);
  }
  for (int i = 1; i <= VAL_MAX; ++i)
    total[i] = total[i - 1] + m_set[cur][i];
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &l, &r);
    printf("%d\n", total[r] - total[l - 1]);
  }
}
int main() {
  program();
  return 0;
}
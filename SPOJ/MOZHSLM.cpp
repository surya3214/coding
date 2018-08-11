// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
char input[BUFF(N_MAX)];
struct {
  int s_l[BUFF(N_MAX)];
  int m_l[BUFF(N_MAX)];
} m_list;
void reset() { m_list.s_l[0] = m_list.m_l[0] = 0; }
void addToList(char x, int idx) {
  int *p;
  if (x == 's') p = m_list.s_l;
  else p = m_list.m_l;
  int pos = ++(p[0]);
  p[pos] = idx;
}
void program() {
  int tcase, n, l, m_at;
  ll ans;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%s", input);
    for (int i = 0; input[i] != '\0'; ++i)
      if (input[i] == 's' || input[i] == 'm')
        addToList(input[i], i);
    l = ans = 0;
    n = m_list.s_l[0];
    for (int i = 1; i <= m_list.m_l[0]; ++i) {
      m_at = m_list.m_l[i];
      while (l + 1 <= n && m_list.s_l[l + 1] < m_at) ++l;
      if (l + 1 > n) break;
      ans += 1LL * l * (n - (l + 1) + 1);
    }
    printf("%lld\n", ans);
  }
}
int main() {
  program();
  return 0;
}
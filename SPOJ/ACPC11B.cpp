// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct P {
  bool type;
  int val;
} points[BUFF(2 * N_MAX)];
int t_abs(int x) { return x > 0 ? x : -x; }
bool m_comparator(P a, P b) {
  return a.val < b.val;
}
void program() {
  int tcase, diff, n1, n2, l, r, x, next;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d", &n1);
    for (int i = 1; i <= n1; ++i)
      scanf("%d", &points[i].val);
    scanf("%d", &n2);
    for (int i = 1; i <= n2; ++i) {
      scanf("%d", &points[n1 + i].val);
      points[n1 + i].type = true;
    }
    x = n1 + n2;
    diff = t_abs(points[1].val - points[x].val);
    sort(points + 1, points + 1 + x, m_comparator);
    l = 0, r = 0;
    while (l <= x && r <= x) {
      if (points[l].val <= points[r].val) {
        next = l + 1;
        while (next <= x) {
          if(!points[next].type && points[next].val != points[l].val) break;
          ++next;
        }
        l = next;
      } else {
        next = r + 1;
        while (next <= x) {
          if (points[next].type && points[next].val != points[r].val) break;
          ++next;
        }
        r = next;
      }
      if (l <= x && r <= x) diff = min(diff, t_abs(points[r].val - points[l].val));
    }
    printf("%d\n", diff);
  }
}
int main() {
  program();
  return 0;
}
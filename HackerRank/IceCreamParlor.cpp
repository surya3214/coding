// AC Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (1e4)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int m, n;
struct {
  int x, y;
} ans;
struct {
  bool seen;
  int x;
} t_cost[BUFF(N_MAX)];
void reset() {
  for (int i = 1; i <= m; ++i)
    t_cost[i].seen = false;
}
void program() {
  int tcase, x;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &m, &n);
    reset();
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &x);
      if (x < m) {
        if (t_cost[m - x].seen) {
          ans.x = t_cost[m - x].x;
          ans.y = i;
        }
        t_cost[x].seen = true;
        t_cost[x].x = i;
      }
    }
    printf("%d %d\n", ans.x, ans.y);
  }
}
int main() {
  program();
  return 0;
}
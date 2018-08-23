// AC
#include <bits/stdc++.h>
#define N_MAX 100000
#define BUFFER 5
#define BUFF(x) x + BUFFER
#pragma GCC optimize "O3"
using namespace std;
int n, q;
struct {
  int first_at;
  int val;
  int unique;
} numbers[BUFF(N_MAX)];
void program() {
  int tcase, l, r;
  int first_at;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &numbers[i].val);
      if (numbers[i - 1].val != numbers[i].val) {
        first_at = i;
        numbers[i].unique = 1;
      } else numbers[i].unique = 0;
      numbers[i].unique += numbers[i - 1].unique;
      numbers[i].first_at = first_at;
    }
    printf("Case %d:\n", t);
    for (int i = 1; i <= q; i++) {
      scanf("%d %d", &l, &r);
      printf("%d\n", numbers[numbers[r].first_at].unique - numbers[numbers[l].first_at - 1].unique);
    }
  }
}
int main() {
  program();
  return 0;
}
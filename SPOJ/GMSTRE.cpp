// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct L {
  int h, e, a, idx;
} levels[BUFF(N_MAX)];
bool m_comparator(L a, L b) {
  if (a.h != b.h) return a.h > b.h;
  if (a.e != b.e) return a.e < b.e;
  return a.a > b.a;
}
void program() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %d", &levels[i].h, &levels[i].e, &levels[i].a);
    levels[i].idx = i;
  }
  if (n == 1) printf("Easiest and Hardest is level 1\n");
  else {
    sort(levels + 1, levels + 1 + n, m_comparator);
    printf("Easiest is level %d\nHardest is level %d\n", levels[1].idx, levels[n].idx);
  }
}
int main() {
  program();
  return 0;
}
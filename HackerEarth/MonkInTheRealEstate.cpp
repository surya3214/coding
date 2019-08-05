// AC Graph Theory, Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e4
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  bool visited;
  int time;
} cities[BUFF(N_MAX)];
int ans, t_ptr;
void reset() {
  ans = 0;
  ++t_ptr;
}
void visit(int u) {
  if (cities[u].time != t_ptr) {
    cities[u].visited = false;
    cities[u].time = t_ptr;
  }
  if (!cities[u].visited) {
    ++ans;
    cities[u].visited = true;
  }
}
void program() {
  int tcase, e, u, v;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t, reset()) {
    scanf("%d", &e);
    for (int i = 1; i <= e; ++i) {
      scanf("%d %d", &u, &v);
      visit(u);
      visit(v);
    }
    printf("%d\n", ans);
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}
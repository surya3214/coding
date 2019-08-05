// AC Graph Theory, DFS, Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  bool visited;
  vector<int> friends;
  ll bananas;
} monkeys[BUFF(N_MAX)];
int n;
ll ans;
void reset() {
  ans = 0;
  for (int i = 0; i <= n; ++i) {
    monkeys[i].bananas = monkeys[i].visited = 0;
    monkeys[i].friends.clear();
  }
}
ll dfs(int u) {
  if (monkeys[u].visited)
    return 0;
  monkeys[u].visited = true;
  ll ret = monkeys[u].bananas;
  for (auto v: monkeys[u].friends)
    ret += dfs(v);
  return ret;
}
void program() {
  int tcase, u, v, m;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &m);
    reset();
    for (int i = 1; i <= m; ++i) {
      scanf("%d %d", &u, &v);
      monkeys[u].friends.push_back(v);
      monkeys[v].friends.push_back(u);
    }
    for (int i = 1; i <= n; ++i)
      scanf("%lld", &monkeys[i].bananas);
    for (int i = 1; i <= n; ++i)
      ans = max(ans, dfs(i));
    printf("%lld\n", ans);
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}
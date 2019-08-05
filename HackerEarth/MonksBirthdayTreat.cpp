// WA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
#define INF (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  int visited;
  vector<int> friends;
} people[BUFF(N_MAX)];
int t_time, ans = INF;
int dfs(int u) {
  if (people[u].visited == t_time)
    return 0;
  people[u].visited = t_time;
  int ret = 1;
  for (auto v: people[u].friends) {
    ret += dfs(v);
    if (ret > ans)
      return INF;
  }
  return ret;
}
void program() {
  int n, d, u, v;
  scanf("%d %d", &n, &d);
  for (int i = 1; i <= d; ++i) {
    scanf("%d %d", &u, &v);
    people[v].friends.push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    ++t_time;
    ans = min(ans, dfs(i));
  }
  printf("%d\n", ans);
}
int main() {
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}
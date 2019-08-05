// AC Graph Theory, DFS, Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m;
struct {
  bool cat, visited;
  vector<int> friends;
} nodes[BUFF(N_MAX)];
int dfs(int u, int l) {
  nodes[u].visited = true;
  if (nodes[u].cat) {
    ++l;
    if (l > m)
      return 0;
  } else l = 0;
  int ret = 0;
  bool is_leaf = true;
  for (auto v: nodes[u].friends) {
    if (!nodes[v].visited) {
      ret += dfs(v, l);
      is_leaf = false;
    }
  }
  if (is_leaf)
    ret = 1;
  return ret;
}
void program() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &nodes[i].cat);
  int u, v;
  for (int i = 1; i < n; ++i) {
    scanf("%d %d", &u, &v);
    nodes[u].friends.push_back(v);
    nodes[v].friends.push_back(u);
  }
  printf("%d\n", dfs(1, 0));
}
int main() {
  program();
  return 0;
}
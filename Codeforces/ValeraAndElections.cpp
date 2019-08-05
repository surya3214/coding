// AC Graph Theory, Medium, DFS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct {
  bool broken;
  int h;
  vector<int> connections;
} cities[BUFF(N_MAX)];
vector<pair<int, int>> roads;
vector<int> ans;
void bfs1(int u, int p, int h) {
  cities[u].h = h;
  for (auto v: cities[u].connections) {
    if (v != p)
      bfs1(v, u, h + 1);
  }
}
bool bfs2(int u, int p) {
  bool ret = false;
  for (auto v: cities[u].connections) {
    if (v != p)
      ret = bfs2(v, u) || ret;
  }
  if (cities[u].broken && !ret) {
    ans.push_back(u);
    ret = true;
  }
  return ret;
}
void program() {
  int u, v, x;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d %d", &u, &v, &x);
    if (x == 2)
      roads.push_back({u, v});
    cities[u].connections.push_back(v);
    cities[v].connections.push_back(u);
  }
  bfs1(1, -1, 0);
  for (auto j: roads) {
    if (cities[j.first].h < cities[j.second].h)
      cities[j.second].broken = true;
    else cities[j.first].broken = true;
  }
  bfs2(1, -1);
  printf("%d\n", ans.size());
  for (auto j: ans)
    printf("%d ", j);
}
int main() {
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}
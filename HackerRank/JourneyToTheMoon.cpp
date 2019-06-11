// AC Union Find, Graph Theory
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, edges;
struct {
  vector<int> edges;
  int g_id;
} vertices[BUFF(N_MAX)];
struct {
  int root, cnt;
  bool visited;
} groups[BUFF(N_MAX)];
int getRootGroup(int x) {
  if (groups[x].root != x)
    groups[x].root = getRootGroup(groups[x].root);
  return groups[x].root;
}
void groupify() {
  int u_grp, v_grp;
  for (int i = 0; i < n; ++i) {
    for (auto j: vertices[i].edges) {
      u_grp = getRootGroup(vertices[i].g_id);
      v_grp = getRootGroup(vertices[j].g_id);
      if (u_grp != v_grp) {
        groups[u_grp].cnt += groups[v_grp].cnt;
        groups[v_grp].root = u_grp;
      }
    }
  }
}
ll getCount() {
  ll ret = 0;
  int x, seen;
  seen = 0;
  for (int i = 0; i < n; ++i) {
    x = getRootGroup(vertices[i].g_id);
    if (!groups[x].visited) {
      seen += groups[x].cnt;
      ret += (1LL * groups[x].cnt * (n - seen));
      groups[x].visited = true;
    }
  }
  return ret;
}
void program() {
  scanf("%d %d", &n, &edges);
  int u, v;
  for (int i = 0; i < n; ++i) {
    vertices[i].g_id = groups[i].root = i;
    groups[i].cnt = 1;
  }
  for (int i = 1; i <= edges; ++i) {
    scanf("%d %d", &u, &v);
    vertices[u].edges.push_back(v);
    vertices[v].edges.push_back(u);
  }
  groupify();
  printf("%lld\n", getCount());
}
int main() {
  program();
  return 0;
}
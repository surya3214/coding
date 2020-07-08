// AC #Medium, #Graph, #Island
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
const int N_MAX =  2e5;
int n, m, t_time;
struct N {
  int a, b, visited;
  vector<int> edges;
} vertices[BUFF(N_MAX)];
struct {
  int c;
  vector<int> nodes;
} highest, ans, tmp;
int tmp_a, tmp_b;
void reset() {
  ++t_time;
  highest.c = ans.c = -1;
}
bool isVisited(int u) { return vertices[u].visited == t_time; }
void markVisited(int u) { vertices[u].visited = t_time; }
void dfs(int u) {
  markVisited(u);
  int tmp_c = (tmp_a + vertices[u].a) / (tmp_b + vertices[u].b);
  if (tmp_c != tmp.c)
    return;
  tmp.nodes.push_back(u);
  for (auto v: vertices[u].edges) {
    if (!isVisited(v)) {
      dfs(v);
    }
  }
}
void resetTemp() {
  tmp_a = tmp_b = 0;
  tmp.c = highest.c;
  tmp.nodes.clear();
}
void updateTemp() {
  if (tmp.c > ans.c ||
     (tmp.c == ans.c && tmp.nodes.size() > ans.nodes.size()))
      ans = tmp;
}
void solve() {
  for (auto u: highest.nodes) {
    if (!isVisited(u)) {
      resetTemp();
      dfs(u);
      updateTemp();
    }
  }
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    reset();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
      cin >> vertices[i].a;
      vertices[i].edges.clear();
    }
    for (int i = 1; i <= n; ++i)
      cin >> vertices[i].b;
    for (int i = 1, u, v; i <= m; ++i) {
      cin >> u >> v;
      vertices[u].edges.push_back(v);
      vertices[v].edges.push_back(u);
    }
    for (int i = 1, c; i <= n; ++i) {
      c = vertices[i].a / vertices[i].b;
      if (c > highest.c) {
        highest.c = c;
        highest.nodes.clear();
      }
      if (c == highest.c)
        highest.nodes.push_back(i);
    }
    solve();
    cout << ans.nodes.size() << endl;
    for (auto u: ans.nodes)
      cout << u << " ";
    cout << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}

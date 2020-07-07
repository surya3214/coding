// AC #Graph, #Medium, #DFS
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
const int N_MAX = 2e5;
int n, m, t;
struct V {
  int parent, depth, t_in, t_out;
  vector<int> edges;
} vertices[BUFF(N_MAX)];
int nodes[BUFF(N_MAX)];
bool m_comparator(int u, int v) { return vertices[u].depth > vertices[v].depth; }
void dfs(int u) {
  vertices[u].t_in = ++t;
  for (auto v: vertices[u].edges) {
    if (v != vertices[u].parent) {
      vertices[v].parent = u;
      vertices[v].depth = vertices[u].depth + 1;
      dfs(v);
    }
  }
  vertices[u].t_out = ++t;
}
bool solve() {
  sort(nodes + 1, nodes + 1 + nodes[0], m_comparator);
  nodes[++nodes[0]] = 1;
  for (int i = 2; i <= nodes[0]; ++i)
    if (nodes[i] != 1)
      nodes[i] = vertices[nodes[i]].parent;
  for (int i = 1, cur, next; i <= nodes[0]; ++i) {
    if (nodes[i] == 1)
      break;
    else {
      cur = nodes[i];
      next = nodes[i + 1];
      if (!(vertices[next].t_in <= vertices[cur].t_in &&
            vertices[cur].t_out <= vertices[next].t_out))
        return false;
    }
  }
  return true;
}
void program() {
  cin >> n >> m;
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    vertices[u].edges.push_back(v);
    vertices[v].edges.push_back(u);
  }
  dfs(1);
  for (int i = 1; i <= m; ++i) {
    cin >> nodes[0];
    for (int j = 1; j <= nodes[0]; ++j)
      cin >> nodes[j];
    cout << (solve() ? "YES" : "NO") << endl;
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

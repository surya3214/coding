// AC #Hard, #Graph, #DFS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n, m, ans1, ans2;
vector<string> types, dirs;
typedef array<int, 2> m_node;
map<char, m_node> moves;
vector<vector<vector<m_node>>> prv;
vector<m_node> cycle;
vector<vector<bool>> vis1, vis2;
unordered_map<int, bool> black_nodes;
void reset() { ans1 = ans2 = 0; }
m_node getNext(m_node& u) {
  m_node nxt = moves[dirs[u[0]][u[1]]];
  return { u[0] + nxt[0], u[1] + nxt[1] };
}
void dfs1(m_node u) {
  if (vis1[u[0]][u[1]]) {
    cycle.push_back(u);
  } else {
    vis1[u[0]][u[1]] = true;
    auto nxt = getNext(u);
    dfs1(nxt);
    if (cycle.back() == nxt && cycle[0] != u)
      cycle.push_back(u);
  }
}
void dfs2(m_node u, int dist) {
  if (vis2[u[0]][u[1]])
    return;
  vis2[u[0]][u[1]] = true;
  if (types[u[0]][u[1]] == '0')
    black_nodes[dist] = true;
  for (auto v: prv[u[0]][u[1]])
    dfs2(v, (dist + 1) % cycle.size());
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    reset();
    cin >> n >> m;
    types = dirs = vector<string>(n);
    for (int i = 0; i < n; ++i)
      cin >> types[i];
    for (int i = 0; i < n; ++i)
      cin >> dirs[i];
    prv = vector<vector<vector<m_node>>>(n, vector<vector<m_node>>(m));
    vis1 = vis2 = vector<vector<bool>>(n, vector<bool>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        m_node u = { i, j };
        m_node v = getNext(u);
        prv[v[0]][v[1]].push_back(u);
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (vis2[i][j])
          continue;
        cycle.clear();
        black_nodes.clear();
        dfs1({ i, j });
        if (!cycle.size())
          continue;
        ans1 += cycle.size();
        dfs2(cycle[0], 0);
        ans2 += black_nodes.size();
      }
    }
    cout << ans1 << " " << ans2 << endl;
  }
}
void ready() {
  moves['U'] = { -1,  0 };
  moves['R'] = {  0,  1 };
  moves['D'] = {  1,  0 };
  moves['L'] = {  0, -1 };
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  ready();
  program();
  return 0;
}
// AC Yeah!! BFS, Ford Fulkerson, Max flow
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
#define A(x) (x * 2)
#define B(x) (A(x) + 1)
void config() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
int n, t, m, src, tgt;
const int N_MAX = 100;
int flow[BUFF(B(N_MAX))][BUFF(B(N_MAX))];
bool bfs(int p[]) {
  bool visited[BUFF(B(n))];
  memset(visited, 0, sizeof(visited));
  queue<int> q;
  for (p[src] = -1, q.push(src), visited[src] = true;
       !q.empty(); q.pop()) {
    int u = q.front();
    for (int v = 1; v <= B(n); ++v) {
      if (!visited[v] && flow[u][v]) {
        p[v] = u;
        if (v == tgt)
          return true;
        q.push(v);
        visited[v] = true;
      }
    }
  }
  return false;
}
int fordFulkerson() {
  int p[BUFF(B(n))];
  int best_flow = 0, min_flow;
  while (bfs(p)) {
    min_flow = INT_MAX;
    for (int v = tgt, u = p[v]; v != src; v = u, u = p[u])
      min_flow = min(min_flow, flow[u][v]);
    for (int v = tgt, u = p[v]; v != src; v = u, u = p[u]) {
      flow[u][v] -= min_flow;
      flow[v][u] += min_flow;
    }
    best_flow += min_flow;
  }
  return best_flow;
}
void program() {
  int c;
  for (cin >> c; c; --c) {
    cin >> n >> t >> m;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n ; ++j)
        flow[A(i)][B(j)] = 0;
      flow[src][A(i)] = t;
      flow[B(i)][tgt] = 1;
    }
    for (int i = 1, v1, v2; i <= m; ++i) {
      cin >> v1 >> v2;
      flow[A(v1)][B(v2)] = 1;
      flow[A(v2)][B(v1)] = 1;
    }
    cout << fordFulkerson() << endl;
  }
}
void ready() {
  src = 0, tgt = 1;
}
int main() {
  ready();
  config();
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}

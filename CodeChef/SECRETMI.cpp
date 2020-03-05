// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 200
#define L_MAX (int) 1e4
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n, m, l;
int dist[BUFF(N_MAX)][BUFF(N_MAX)], min_dist[BUFF(N_MAX)][BUFF(N_MAX)];
int path[BUFF(L_MAX)];
void reset() {
  memset(dist, 0x3f, sizeof(dist));
}
void program() {
  reset();
  cin >> n >> m >> l;
  for (int i = 1; i <= l; ++i)
    cin >> path[i];
  for (int i = 1, u, v, w; i <= m; ++i) {
    cin >> u >> v >> w;
    dist[u][v] = w;
    dist[v][u] = w;
  }
  memcpy(min_dist, dist, sizeof(dist));
  for (int i = 1; i <= n; ++i)
    min_dist[i][i] = 0;
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        min_dist[i][j] = min(min_dist[i][j], min_dist[i][k] + min_dist[k][j]);
      }
    }
  }
  int ans = 1;
  for (int i = 1, j = 1, u, v, d; i < l; i = j, ++ans) {
    u = path[i];
    j = i + 1;
    d = 1;
    while (j <= l) {
      v = path[j];
      if (d > min_dist[u][v])
        break;
      ++d;
      ++j;
    }
    --j;
    if (i == j) {
      cout << "-1" << endl;
      return;
    }
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--)
    program();
  return 0;
}
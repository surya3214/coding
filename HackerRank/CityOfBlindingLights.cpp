// AC Floyd Warshall, Graph Theory
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 400
#define INF (int) 1e9
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m;
int dist[BUFF(N_MAX)][BUFF(N_MAX)];
void floydWarshall() {
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (dist[i][k] && dist[k][j] && (dist[i][k] + dist[k][j] < dist[i][j]))
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }
}
void program() {
  int u, v, r, q;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      dist[i][j] = (i == j) ? 0 : INF;
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d %d", &u, &v, &r);
    dist[u][v] = r;
  }
  floydWarshall();
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &u, &v);
    if (dist[u][v] == INF)
      printf("-1\n");
    else printf("%d\n", dist[u][v]);
  }
}
int main() {
  program();
  return 0;
}
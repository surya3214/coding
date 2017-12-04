// AC
#include <iostream>
#include <cstdio>
#define N_MAX 100010
#define INF 1E11
using namespace std;
int n, m, clib, croad;
long long int ans;
int groups[N_MAX];
int ranks[N_MAX];
bool visited[N_MAX];
void reset() {
  ans = 0;
  for (int i = 0; i <= n; i++)
    groups[i] = -1, ranks[i] = 1, visited[i] = false;
}
int findGroups(int u) {
  if (groups[u] == -1)
    return u;
  return findGroups(groups[u]);
}
void groupify(int u, int v) {
  int g_u = findGroups(u);
  int g_v = findGroups(v);
  if (g_u != g_v) {
    if (ranks[g_u] >= ranks[g_v]) {
      groups[g_v] = groups[v] = g_u;
      ranks[g_u] += ranks[g_v];
    } else {
      groups[g_u] = groups[u] = g_v;
      ranks[g_v] += ranks[g_u];
    }
  }  
}
void program() {
  int q, u, v, g_u;
  long long int tmp;
  scanf("%d", &q);
  while (q--) {
    scanf("%d %d %d %d", &n, &m, &clib, &croad);
    reset();
    for (int i = 0; i < m; i++) {
      scanf("%d %d", &u, &v);
      groupify(u, v); 
    }
    for (int i = 1; i <= n; i++) {
      g_u = findGroups(i);
      tmp = INF;
      if (!visited[g_u]) {
        visited[g_u] = true;
        tmp = (long long) clib * ranks[g_u];
        tmp = min(tmp, clib + ((long long) croad * (ranks[g_u] - 1)));
        ans += tmp;
        // for (int i = ranks[g_u]; i > 0; i--)
        //   tmp = min(tmp, (long long) (ranks[g_u] - i + 1) * clib + (long long) croad * (i - 1));
        // ans += tmp;
      }
    }
    printf("%lld\n", ans);
  }
}
int main() {
  // freopen("TorqueAndDevelopment_input.txt", "r", stdin);
  program();
  return 0;
}
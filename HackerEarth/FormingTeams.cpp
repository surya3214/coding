// WA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, k, ceo;
struct {
  vector<int> v;
  int max_rank;
  int min_rank;
  int rank;
  bool is_ceo;
  int sets_needed;
} nodes[BUFF(N_MAX)];
void reset() {
  for (int i = 1; i <= n; ++i) {
    nodes[i].v.clear();
    nodes[i].is_ceo = true;
  }
}
int t_abs(int x) { return x > 0 ? x : -x; }
void dfs(int u) {
  nodes[u].max_rank = nodes[u].min_rank = nodes[u].rank;
  int v;
  for (int i = 0; i < nodes[u].v.size(); ++i) {
    v = nodes[u].v[i];
    dfs(v);
    nodes[u].max_rank = max(nodes[u].max_rank, nodes[v].max_rank);
    nodes[u].min_rank = min(nodes[u].min_rank, nodes[v].min_rank);
  }
}
int diff, k_left;
void compute(int u) {
  nodes[u].sets_needed = 1;
  int v, t;
  for (int i = 0; i < nodes[u].v.size(); ++i) {
    v = nodes[u].v[i];
    compute(v);
    t = t_abs(nodes[u].rank - nodes[v].max_rank);
    t = max(t, t_abs(nodes[u].rank - nodes[v].min_rank));
    if (t > diff)
      nodes[u].sets_needed += nodes[v].sets_needed;
  }
}
int findCEO() {
  for (int i = 1; i <= n; ++i)
    if (nodes[i].is_ceo)
      return i;
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int findBS() {
  int l, r, mid;
  l = 0;
  r = 1e9;
  while (l <= r) {
    diff = mid = getMid(l, r);
    k_left = k;
    compute(ceo);
    if (nodes[ceo].sets_needed <= k)
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
void program() {
  int tcase, u, v;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &k);
    reset();
    for (int i = 1; i <= n; ++i)
      scanf("%d", &nodes[i].rank);
    for (int i = 1; i < n; ++i) {
      scanf("%d %d", &u, &v);
      nodes[u].v.push_back(v);
      nodes[v].is_ceo = false;
    }
    ceo = findCEO();
    dfs(ceo);
    printf("%d\n", findBS());
  }
}
int main() {
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}
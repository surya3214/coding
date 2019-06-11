// AC Graph Theory, Union Find
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
#define N_MAX (int) 1e5
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m, extra_edges;
ll g_total, p_total;
struct {
  int root, size, edges;
  bool visited;
} groups[BUFF(N_MAX)];
int s_groups[BUFF(N_MAX)];
int s_ptr;
void reset() {
  g_total = p_total = s_ptr = extra_edges = 0;
  for (int i = 1; i <= n; ++i) {
    groups[i].root = i;
    groups[i].size = 1;
    groups[i].edges = 0;
    groups[i].visited = false;
  }
}
int findGroupRoot(int x) {
  if (groups[x].root != x)
    groups[x].root = findGroupRoot(groups[x].root);
  return groups[x].root;
}
void groupify(int u, int v) {
  int u_grp, v_grp;
  u_grp = findGroupRoot(u);
  v_grp = findGroupRoot(v);
  if (u_grp != v_grp) {
    groups[v_grp].root = u_grp;
    groups[u_grp].size += groups[v_grp].size;
    groups[u_grp].edges += groups[v_grp].edges;
  }
  ++groups[u_grp].edges;
}
void addToSorted(int x) { s_groups[++s_ptr] = x; }
bool s_comparator(int x, int y) { return groups[x].size > groups[y].size; }
void identifyComponents() {
  int grp;
  for (int i = 1; i <= n; ++i) {
    grp = findGroupRoot(i);
    if (!groups[grp].visited && groups[grp].edges) {
      addToSorted(grp);
      groups[grp].visited = true;
    }
  }
  sort(s_groups + 1, s_groups + 1 + s_ptr, s_comparator);
}
void processComponents() {
  int x;
  ll t;
  for (int i = 1; i <= s_ptr; ++i) {
    x = s_groups[i];
    t = 0;
    for (int j = 1; j < groups[x].size; ++j) {
      t = 1LL * j * (j + 1);
      g_total += p_total + t;
    }
    p_total += t;
    extra_edges += groups[x].edges - (groups[x].size - 1);
  }
  g_total += p_total * extra_edges;
}
void program() {
  int q, u, v;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &n, &m);
    reset();
    for (int i = 1; i <= m; ++i) {
      scanf("%d %d", &u, &v);
      groupify(u, v);
    }
    identifyComponents();
    processComponents();
    printf("%lld\n", g_total);
  }
}
int main() {
  program();
  return 0;
}
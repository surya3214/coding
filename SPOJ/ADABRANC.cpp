// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 2 * 100000
#define M_MAX 2 * 100000
#define Q_MAX 3 * 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n;
struct E {
  bool type;
  int u, v, weight;
} events[BUFF(M_MAX + Q_MAX)];
int ans[BUFF(Q_MAX)];
int parent[BUFF(N_MAX)];
int ranks[BUFF(N_MAX)];
int findParentOf(int u) {
  if (parent[u] == u) return u;
  else return parent[u] = findParentOf(parent[u]);
}
int unionize(int u, int v) {
  int u_parent, v_parent;
  u_parent = findParentOf(u);
  v_parent = findParentOf(v);
  if (u_parent != v_parent) {
    if (ranks[v_parent] > ranks[u_parent]) {
      ranks[v_parent] += ranks[u_parent];
      parent[u_parent] = parent[u] = v_parent;
    } else {
      ranks[u_parent] += ranks[v_parent];
      parent[v_parent] = parent[v] = u_parent;
    }
  }
}
bool m_comparator(E a, E b) {
  if (a.weight != b.weight)
    return a.weight > b.weight;
  return a.type < b.type;
}
void reset() {
  for (int i = 1; i <= n; ++i)
    parent[i] = i, ranks[i] = 1;
}
void program() {
  int m, q;
  scanf("%d %d %d", &n, &m, &q);
  reset();
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d %d", &events[i].u, &events[i].v, &events[i].weight);
    ++events[i].u;
    ++events[i].v;
    events[i].type = 0;
  }
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &events[m + i].u, &events[m + i].weight);
    ++events[m + i].u;
    events[m + i].v = i;
    events[m + i].type = 1;
  }
  sort(events + 1, events + 1 + m + q, m_comparator);
  for (int i = 1; i <= m + q; ++i) {
    if (events[i].type)
      ans[events[i].v] = ranks[findParentOf(events[i].u)];
    else unionize(events[i].u, events[i].v);
  }
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
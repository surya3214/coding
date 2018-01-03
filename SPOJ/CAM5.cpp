// WA
#include <iostream>
#include <cstdio>
#define N_MAX 100010
using namespace std;
int n, e, cnt;
int parent[N_MAX];
int ranks[N_MAX];
bool visited[N_MAX];
int find_parent(int u, int val) {
  if (parent[u] == -1) {
    if (u != val)
      parent[val] = u;
    return u;
  } else return parent[u];
}
void unionize(int u, int v) {
  int p_u = find_parent(u, u);
  int p_v = find_parent(v, v);
  if (p_u == p_v)
    return;
  else if (ranks[p_u] >= ranks[p_v]) {
    parent[v] = parent[p_v] = p_u;
    ranks[p_u] += ranks[p_v];
  } else {
    parent[u] = parent[p_u] = p_v;
    ranks[p_v] += ranks[p_u];
  }
}
void reset() {
  cnt = 0;
  for (int i = 0; i <= n; i++)
    parent[i] = -1, ranks[i] = 1, visited[i] = false;
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    scanf("%d", &e);
    reset();
    int u, v;
    for (int i = 0; i < e; i++) {
      scanf("%d %d", &u, &v);
      unionize(u, v);
    }
    int parent;
    for (int i = 0; i < n; i++) {
      parent = find_parent(i, i);
      if (!visited[parent]) {
        visited[parent] = true;
        cnt++;
      }
    }
    printf("%d\n", cnt);
  }
}
int main() {
  program();
  return 0;
}
// AC
#include <iostream>
#include <cstdio>
#define N_MAX 100010
using namespace std;
int edges_list[N_MAX], edge_connects_to[N_MAX << 1], edge_next[N_MAX << 1];
// edges_list & edge_next contain only edge_labels whereas edge_connects_to contains node labels
bool visited[N_MAX];
int edge_label, eccentricity, max_edge, n;
void reset() {
  for (int i = 0; i < n; i++)
    edges_list[i] = -1;
  edge_label = eccentricity = max_edge = 0;
}
void dfsUtil(int edge, int dist) {
  if (visited[edge])
    return;
  if (dist > eccentricity) {
    eccentricity = dist;
    max_edge = edge;
  }
  visited[edge] = true;
  int next_edge = edges_list[edge];
  while (next_edge != -1) {
    dfsUtil(edge_connects_to[next_edge], dist + 1);
    next_edge = edge_next[next_edge];
  }
  visited[edge] = false;
}
void dfs() {
  dfsUtil(0, 0);
  dfsUtil(max_edge, 0);
}
void program() {
  int t, u, v;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    reset();
    while (--n) {
      scanf("%d %d", &u, &v);
      // connect u to v
      edge_connects_to[edge_label] = v, edge_next[edge_label] = edges_list[u], edges_list[u] = edge_label;
      edge_label++;
      // connect v to u
      edge_connects_to[edge_label] = u, edge_next[edge_label] = edges_list[v], edges_list[v] = edge_label;
      edge_label++;
    }
    dfs();
    printf("%d\n", (1 + eccentricity) >> 1);
  }
}
int main() {
  program();
  return 0;
}
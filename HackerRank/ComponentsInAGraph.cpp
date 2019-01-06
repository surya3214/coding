// AC DFS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 15000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct {
  bool visited;
  int size;
  vector<int> edges;
} nodes[BUFF(2 * N_MAX)];
struct {
  int min, max;
} ans;
void updateAns(int x) {
  if (!ans.min)
    ans.min = ans.max = x;
  else {
    ans.min = min(ans.min, x);
    ans.max = max(ans.max, x);
  }
}
int calculateSize(int u) {
  if (nodes[u].visited)
    return 0;
  nodes[u].visited = true;
  nodes[u].size = 1;
  for (int i = 0; i < nodes[u].edges.size(); ++i)
    nodes[u].size += calculateSize(nodes[u].edges[i]);
  return nodes[u].size;
}
void program() {
  int u, v;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &u, &v);
    nodes[u].edges.push_back(v);
    nodes[v].edges.push_back(u);
  }
  for (int i = 1; i <= (2 * n); ++i) {
    if (!nodes[i].visited) {
      calculateSize(i);
      if (nodes[i].size != 1)
        updateAns(nodes[i].size);
    }
  }
  printf("%d %d", ans.min, ans.max);
}
int main() {
  program();
  return 0;
}
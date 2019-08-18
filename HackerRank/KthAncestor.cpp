// AC Tree, Binary uplifting
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define H_MAX 20
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
struct {
  bool present;
  int depth, parent[BUFF(H_MAX)];
  vector<int> adj;
} nodes[BUFF(N_MAX)];
int powers[BUFF(H_MAX)];
int root;
void reset() {
  for (int i = 1; i <= N_MAX; ++i) {
    for (int j = 0; j < H_MAX; ++j)
      nodes[i].parent[j] = 0;
    nodes[i].adj.clear();
    nodes[i].present = false;
  }
}
void updateOneLevelInfo(int cur, int prev) {
  nodes[cur].present = true;
  nodes[cur].depth = nodes[prev].depth + 1;
  nodes[cur].parent[0] = prev;
  for (int i = 0; i < H_MAX; ++i)
    nodes[cur].parent[i + 1] = nodes[nodes[cur].parent[i]].parent[i];
}
void dfs(int cur, int prev) {
  nodes[cur].present = true;
  nodes[cur].depth = nodes[prev].depth + 1;
  nodes[cur].parent[0] = prev;
  for (auto v: nodes[cur].adj) {
    if (v != prev)
      dfs(v, cur);
  }
}
void process() {
  dfs(root, 0);
  for (int i = 0; i < H_MAX; ++i)
    for (int j = 1; j <= N_MAX; ++j)
      nodes[j].parent[i + 1] = nodes[nodes[j].parent[i]].parent[i];
}
int findKthAncestor(int x, int k) {
  if (!nodes[x].present || nodes[x].depth < k)
    return 0;
  for (int i = H_MAX - 1; i >= 0; --i) {
    if (powers[i] <= k) {
      x = nodes[x].parent[i];
      k -= powers[i];
    }
  }
  return x;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1, p, x, y, q, type; t <= tcase; ++t) {
    reset();
    scanf("%d", &p);
    for (int i = 1; i <= p; ++i) {
      scanf("%d %d", &x, &y);
      if (!y)
        root = x;
      else {
        nodes[x].adj.push_back(y);
        nodes[y].adj.push_back(x);
      }
    }
    process();
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
      scanf("%d", &type);
      switch (type) {
        case 0:
          scanf("%d %d", &y, &x);
          updateOneLevelInfo(x, y);
          break;
        case 1:
          scanf("%d", &x);
          nodes[x].present = false;
          break;
        case 2:
          scanf("%d %d", &x, &y);
          printf("%d\n", findKthAncestor(x, y));
          break;
      }
    }
  }
}
void ready() {
  int ret = 1;
  for (int i = 0; i < H_MAX; ++i) {
    powers[i] = ret;
    ret = ret << 1;
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  ready();
  program();
  return 0;
}
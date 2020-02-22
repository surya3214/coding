// AC DFS, LCA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define H_MAX 17
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
struct {
  int depth, sum;
  ll ans;
  int parent[BUFF(H_MAX)];
  vector<int> friends;
} vertices[BUFF(N_MAX)];
void dfs(int cur, int prev) {
  vertices[cur].depth = vertices[prev].depth + 1;
  vertices[cur].parent[0] = prev;
  for (int i = 1, half; i <= H_MAX; ++i) {
    half = vertices[cur].parent[i - 1];
    vertices[cur].parent[i] = vertices[half].parent[i - 1];
  }
  for (auto next: vertices[cur].friends)
    if (next != prev)
      dfs(next, cur);
}
int findLCA(int u, int v) {
  if (vertices[u].depth < vertices[v].depth)
    swap(u, v);
  for (int i = H_MAX, lvl = (1 << H_MAX), diff = vertices[u].depth - vertices[v].depth;
       i >= 0 && diff; --i, lvl >>= 1) {
    if (diff >= lvl) {
      u = vertices[u].parent[i];
      diff -= lvl;
    }
  }
  if (u != v) {
    for (int i = H_MAX; i >= 0; --i) {
      if (vertices[u].parent[i] != vertices[v].parent[i]) {
        u = vertices[u].parent[i];
        v = vertices[v].parent[i];
      }
    }
    u = vertices[u].parent[0];
  }
  return u;
}
void findIntersection(int u1, int v1, int u2, int v2) {
  if (v2 != findLCA(u1, v2))
    return;
  int l1 = findLCA(u1, u2);
  if (vertices[l1].depth <= vertices[v1].depth)
    return;
  int sx, ex;
  sx = findLCA(u1, l1);
  ex = (vertices[v2].depth >= vertices[v1].depth) ? v2 : v1;
  --vertices[sx].sum;
  ++vertices[ex].sum;
}
void computeSum(int cur, int prev) {
  for (auto next: vertices[cur].friends) {
    if (next != prev) {
      computeSum(next, cur);
      vertices[cur].sum += vertices[next].sum;
    }
  }
}
void computeAns(int cur, int prev) {
  vertices[cur].ans = vertices[cur].sum + vertices[prev].ans;
  for (auto next: vertices[cur].friends)
    if (next != prev)
      computeAns(next, cur);
}
void program() {
  int m1, m2;
  scanf("%d %d %d", &n, &m1, &m2);
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d %d", &u, &v);
    vertices[u].friends.push_back(v);
    vertices[v].friends.push_back(u);
  }
  dfs(1, 0);
  for (int i = 1, a, b, c, d, l1, l2; i <= m1; ++i) {
    scanf("%d %d %d %d", &a, &b, &c, &d);
    l1 = findLCA(a, b);
    l2 = findLCA(c, d);
    ++vertices[a].sum;
    ++vertices[b].sum;
    vertices[l1].sum -= 2;
    findIntersection(a, l1, c, l2);
    findIntersection(a, l1, d, l2);
    findIntersection(b, l1, c, l2);
    findIntersection(b, l1, d, l2);
  }
  computeSum(1, 0);
  computeAns(1, 0);
  ll ans;
  for (int i = 1, u, v, l; i <= m2; ++i) {
    scanf("%d %d", &u, &v);
    l = findLCA(u, v);
    ans = vertices[u].ans + vertices[v].ans - (2 * 1LL * vertices[l].ans);
    printf("%lld\n", ans);
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}

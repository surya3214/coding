// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define H_MAX 31
#define NODES_MAX (int) (N_MAX * H_MAX)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
map<int, int> M;
int root, c_ids;
int powers[BUFF(H_MAX)];
struct {
  int key, parent, root;
  vector<int> adj;
} stations[BUFF(N_MAX)];
struct {
  int l, r, cnt;
} nodes_pool[BUFF(NODES_MAX)];
int nodes_ptr;
int number_buffer[BUFF(BITS_MAX)];
void fillBuffer(int x) {
  for (int i = BITS_MAX; i >= 0; --i) {
    number_buffer[i] = x & 1;
    if (x)
      x = x >> 1;
  }
}
void invertBuffer() {
  for (int i = BITS_MAX; i >= 0; --i)
    number_buffer[i] = !number_buffer[i];
}
int insertIntoTrie(int prev) {
  int ret, cur, next;
  ret = next = ++nodes_ptr;
  nodes[next] = nodes[prev];
  cur = next;
  ++nodes[cur].cnt;
  for (int i = 0; i <= BITS_MAX; ++i) {
    next = ++nodes_ptr;
    if (number_buffer[i]) {
      nodes[next] = nodes[prev].r;
      nodes[cur].r = next;
    } else {
      nodes[next] = nodes[prev].l;
      nodes[cur].l = next;
    }
    cur = next;
    ++nodes[cur].cnt;
  }
  return ret;
}
void fillSingleNodeInfo(int cur, int prev) {
  stations[cur].parent = prev;
  fillBuffer(stations[cur].key);
  stations[cur].root = insertIntoTrie(stations[prev].root);
}
void dfs(int cur, int prev) {
  fillSingleNodeInfo(cur, prev);
  for (auto v: stations[cur].adj)
    if (v != prev)
      dfs(v, cur);
}
void process() {
  dfs(root, 0);
}
int findClosest(int cur) {
  int ret = 0;
  for (int i = 0, pos = 0; i <= BITS_MAX; ++i) {
    if (number_buffer[i]) {

    } else {

    }
  }
  return ret;
}
void program() {
  int n, q, u, v, k, r, key;
  scanf("%d %d", &n, &q);
  scanf("%d %d", &r, &key);
  root = M[r] = ++c_ids;
  stations[M[r]].key = key;
  for (int i = 1; i < n; ++i) {
    scanf("%d %d %d", &u, &v, &k);
    if (!M[u]) {
      M[u] = ++c_ids;
      stations[M[u]].key = k;
    } else if (!M[v]) {
      M[v] = ++c_ids;
      stations[M[v]].key = k;
    }
    stations[M[u]].adj.push_back(M[v]);
    stations[M[v]].adj.push_back(M[u]);
  }
  process();
  for (int i = 1, type, a, b; i <= q; ++i) {
    scanf("%d", &type);
    if (!type) {
      scanf("%d %d %d", &v, &u, &k);
      M[u] = ++c_ids;
      stations[M[u]].key = k;
      fillSingleNodeInfo(M[u], M[v]);
    } else {
      scanf("%d %d", &v, &k);
      fillBuffer(k);
      a = findClosest(stations[M[v]].root);
      invertBuffer();
      b = findClosest(stations[M[v]].root);
      printf("%d %d\n", a, b);
    }
  }
}
void ready() {
  int ret = 1;
  for (int i = 0; i <= H_MAX; ++i, ret = ret << 1)
    powers[i] = ret;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  ready();
  program();
  return 0;
}
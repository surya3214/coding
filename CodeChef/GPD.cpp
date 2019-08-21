// AC Persistent Trie
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define Q_MAX (int) 2e5
#define BITS_MAX 31
#define NODES_MAX (int) ((N_MAX + Q_MAX) * BITS_MAX)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
map<int, int> M;
int root, c_ids;
int powers[BUFF(BITS_MAX)];
struct {
  int key, root;
  vector<int> adj;
} stations[BUFF(N_MAX + Q_MAX)];
struct {
  int l, r, cnt;
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int number_buffer[BUFF(BITS_MAX)];
void fillBuffer(int x) {
  for (int i = BITS_MAX; i; --i) {
    number_buffer[i] = x & 1;
    if (x)
      x = x >> 1;
  }
}
void invertBuffer() {
  for (int i = BITS_MAX; i; --i)
    number_buffer[i] = !number_buffer[i];
}
int insertIntoTrie(int prev) {
  int ret, cur, next;
  ret = next = ++nodes_ptr;
  nodes[next] = nodes[prev];
  cur = next;
  ++nodes[cur].cnt;
  for (int i = 1; i <= BITS_MAX; ++i) {
    next = ++nodes_ptr;
    assert(nodes_ptr <= NODES_MAX);
    if (number_buffer[i]) {
      nodes[next] = nodes[nodes[prev].r];
      nodes[cur].r = next;
      prev = nodes[prev].r;
    } else {
      nodes[next] = nodes[nodes[prev].l];
      nodes[cur].l = next;
      prev = nodes[prev].l;
    }
    cur = next;
    ++nodes[cur].cnt;
  }
  return ret;
}
void fillSingleNodeInfo(int cur, int prev) {
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
  bool left;
  for (int i = 1; i <= BITS_MAX; ++i) {
    if (number_buffer[i]) {
      if (nodes[nodes[cur].r].cnt)
        left = false;
      else left = true;
    } else {
      if (nodes[nodes[cur].l].cnt)
        left = true;
      else left = false;
    }
    if (left)
      cur = nodes[cur].l;
    else {
      ret += powers[i];
      cur = nodes[cur].r;
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
    M[u] = ++c_ids;
    stations[M[u]].key = k;
    stations[M[u]].adj.push_back(M[v]);
    stations[M[v]].adj.push_back(M[u]);
  }
  process();
  for (int i = 1, ans = 0, type, a, b; i <= q; ++i) {
    scanf("%d", &type);
    type ^= ans;
    if (!type) {
      scanf("%d %d %d", &v, &u, &k);
      v ^= ans;
      u ^= ans;
      k ^= ans;
      M[u] = ++c_ids;
      stations[M[u]].key = k;
      fillSingleNodeInfo(M[u], M[v]);
    } else {
      scanf("%d %d", &v, &k);
      v ^= ans;
      k ^= ans;
      fillBuffer(k);
      a = findClosest(stations[M[v]].root) ^ k;
      invertBuffer();
      b = findClosest(stations[M[v]].root) ^ k;
      printf("%d %d\n", a, b);
      ans = a ^ b;
    }
  }
}
void ready() {
  for (int i = BITS_MAX, ret = 1; i; --i, ret = ret << 1)
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
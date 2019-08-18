// AC Persistent Trie, Hard
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define BITS_MAX 20
#define N_MAX (int) (5e5)
#define NODES_MAX (int) (N_MAX * BITS_MAX)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
struct N {
  int l, r, cnt;
  N() {}
  N(int l, int r, int cnt) : cnt(cnt), l(l), r(r) {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int state, roots[BUFF(N_MAX)];
int number_buffer[BUFF(BITS_MAX)], powers[BUFF(BITS_MAX)];
void fillBuffer(int x, bool invert = false) {
  for (int i = BITS_MAX; i; --i) {
    number_buffer[i] = x & 1;
    if (invert)
      number_buffer[i] = !number_buffer[i];
    if (x)
      x = x >> 1;
  }
}
int insertIntoTrie(int prev) {
  int cur, ret, next;
  ret = next = ++nodes_ptr;
  nodes[next] = nodes[prev];
  cur = next;
  ++nodes[cur].cnt;
  bool left;
  for (int i = 1; i <= BITS_MAX; ++i) {
    next = ++nodes_ptr;
    left = !(number_buffer[i]);
    if (left) {
      nodes[next] = nodes[nodes[prev].l];
      nodes[cur].l = next;
      prev = nodes[prev].l;
    } else {
      nodes[next] = nodes[nodes[prev].r];
      nodes[cur].r = next;
      prev = nodes[prev].r;
    }
    cur = next;
    ++nodes[cur].cnt;
  }
  return ret;
}
int findClosest(int l, int r) {
  int a, b, ret;
  a = roots[l - 1];
  b = roots[r];
  ret = 0;
  bool left;
  for (int i = 1, pos = 1; i <= BITS_MAX; ++i, ++pos) {
    if (number_buffer[i])
      left = (nodes[nodes[b].r].cnt - nodes[nodes[a].r].cnt) ? false : true;
    else left = (nodes[nodes[b].l].cnt - nodes[nodes[a].l].cnt) ? true : false;
    if (left) {
      a = nodes[a].l;
      b = nodes[b].l;
    } else {
      a = nodes[a].r;
      b = nodes[b].r;
      ret += powers[pos];
    }
  }
  return ret;
}
int findLessCount(int l, int r) {
  int a, b, ret;
  a = roots[l - 1];
  b = roots[r];
  ret = 0;
  for (int i = 1; i <= BITS_MAX; ++i) {
    if (number_buffer[i]) {
      ret += nodes[nodes[b].l].cnt - nodes[nodes[a].l].cnt;
      if (nodes[nodes[b].r].cnt - nodes[nodes[a].r].cnt) {
        a = nodes[a].r;
        b = nodes[b].r;
      } else break;
    } else {
      if (nodes[nodes[b].l].cnt - nodes[nodes[a].l].cnt) {
        a = nodes[a].l;
        b = nodes[b].l;
      } else break;
    }
  }
  if (!nodes[b].l && !nodes[b].r) // leaf node
    ret += nodes[b].cnt - nodes[a].cnt;
  return ret;
}
int findKth(int l, int r, int k) {
  int a, b, ret, cnt;
  a = roots[l - 1];
  b = roots[r];
  ret = 0;
  for (int cnt, pos = 1; (nodes[b].l || nodes[b].r); ++pos) {
    cnt = nodes[nodes[b].l].cnt - nodes[nodes[a].l].cnt;
    if (k <= cnt) {
      a = nodes[a].l;
      b = nodes[b].l;
    } else {
      k -= cnt;
      ret += powers[pos];
      a = nodes[a].r;
      b = nodes[b].r;
    }
  }
  return ret;
}
void program() {
  int q;
  scanf("%d", &q);
  for (int i = 1, type, l, r, x; i <= q; ++i) {
    scanf("%d", &type);
    switch (type) {
      case 0:
        scanf("%d", &x);
        fillBuffer(x);
        ++state;
        roots[state] = insertIntoTrie(roots[state - 1]);
        break;
      case 1:
        scanf("%d %d %d", &l, &r, &x);
        fillBuffer(x, true);
        printf("%d\n", findClosest(l, r));
        break;
      case 2:
        scanf("%d", &x);
        state -= x;
        break;
      case 3:
        scanf("%d %d %d", &l, &r, &x);
        fillBuffer(x);
        printf("%d\n", findLessCount(l, r));
        break;
      case 4:
        scanf("%d %d %d", &l, &r, &x);
        printf("%d\n", findKth(l, r, x));
        break;
    }
  }
}
void ready() {
  int ret = 1;
  for (int i = BITS_MAX; i; --i) {
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
// TLE
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define Q_MAX 200000
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int total_nodes;
struct {
  ll max_child_sum;
  ll total_val;
  int parent;
  int height;
  ll lazy_update;
} nodes[BUFF(Q_MAX)];
void init(int idx, int parent, ll val) {
  nodes[idx].parent = parent;
  nodes[idx].total_val = val;
  nodes[idx].max_child_sum = 0;
  nodes[idx].height = nodes[parent].height + 1;
  nodes[idx].lazy_update = val;
}
void lazyUpdate(int x) {
  if (!nodes[x].lazy_update)
    return;
  ll c_val, pending_val;
  pending_val = c_val = 0;
  while (x) {
    nodes[x].total_val += pending_val;
    nodes[x].max_child_sum = max(nodes[x].max_child_sum, c_val);
    c_val = nodes[x].total_val;
    if (nodes[x].lazy_update) {
      pending_val += nodes[x].lazy_update;
      nodes[x].lazy_update = 0;
    }
    x = nodes[x].parent;
  }
}
struct E {
  int x, h;
} events[BUFF(Q_MAX)];
int e_ptr;
void addToEvents(int x, int h) {
  ++e_ptr;
  events[e_ptr].x = x;
  events[e_ptr].h = h;
}
bool e_comparator(E a, E b) {
  if (a.h != b.h)
    return a.h > b.h;
  return a.x < b.x;
}
void processPending() {
  if (!e_ptr) return;
  sort(events + 1, events + 1 + e_ptr, e_comparator);
  for (int i = 1; i <= e_ptr; ++i)
    lazyUpdate(events[i].x);
  e_ptr = 0;
}
void program() {
  int q, x, y, type;
  init(++total_nodes, 0, 0);
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &type);
    if (type == 1) {
      scanf("%d %d", &x, &y);
      init(++total_nodes, x, y);
      addToEvents(total_nodes, nodes[total_nodes].height);
    } else if (type == 2) {
      processPending();
      scanf("%d", &x);
      printf("%lld\n", nodes[x].max_child_sum);
    }
  }
}
int main() {
  program();
  return 0;
}
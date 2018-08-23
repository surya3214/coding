// AC - SQRT decomposition, Offline, Query events sorting
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (3 * 1e5)
#define Q_MAX (int) (3 * 1e5)
#define BLOCKS_MAX 112
#define BLOCKS_SIZE 2930
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n, q;
int ans[BUFF(Q_MAX)];
int trees_h[BUFF(N_MAX)];
struct {
  int max_h;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
struct E {
  bool type;
  int weight;
  int l, r, idx;
} events[BUFF(N_MAX + Q_MAX)];
int getBlockNumber(int i) { return (i - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
bool m_comparator(E a, E b) {
  if (a.weight != b.weight)
    return a.weight < b.weight;
  return a.type < b.type;
}
int findMaximum(int l, int r) {
  int blk_id, blk_l, blk_r;
  int ret = 0;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    if (l == blk_l && blk_r <= r) {
      ret = max(ret, blocks[blk_id].max_h);
      l = blk_r + 1;
    } else {
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i)
        ret = max(ret, trees_h[i]);
      l = t_r + 1;
    }
  }
  return ret;
}
int getSquareRootOf(int x) {
  int i = 2;
  while (i * i <= x) ++i;
  return --i;
}
void program() {
  int x;
  scanf("%d %d", &n, &q);
  block_size = BLOCKS_SIZE;
  // block_size = getSquareRootOf(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &events[i].weight);
    events[i].type = false;
    events[i].idx = i;
  }
  for (int i = 1; i <= q; ++i) {
    x = n + i;
    scanf("%d %d %d", &events[x].l, &events[x].r, &events[x].weight);
    ++events[x].l;
    ++events[x].r;
    events[x].idx = i;
    events[x].type = true;
  }
  sort(events + 1, events + 1 + n + q, m_comparator);
  for (int i = 1; i <= n + q; ++i) {
    if (events[i].type)
      ans[events[i].idx] = findMaximum(events[i].l, events[i].r);
    else {
      trees_h[events[i].idx] = events[i].weight;
      blocks[getBlockNumber(events[i].idx)].max_h = events[i].weight;
    }
  }
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
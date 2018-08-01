// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define BLOCKS_MAX 317
using namespace std;
typedef long long int ll;
int n;
struct E {
  int v;
  struct E *next;
} edges[BUFF(N_MAX)];
int edges_ptr;
struct {
  ll animals;
  int l_idx;
  struct E *children;
  bool vps;
} nodes[BUFF(N_MAX)];
struct {
  int animal_idx;
  int until;
} linearized_tree[BUFF(N_MAX)];
int l_ptr;
struct {
  int dirty;
  ll sum;
} blocks[BUFF(BLOCKS_MAX)];
int block_size;
int vps_coverage[BUFF(N_MAX)];
struct E *getEdgesFromPool() { return &edges[edges_ptr++]; }
void addToEdges(int u, int v) {
  struct E *t = getEdgesFromPool();
  t->v = v;
  t->next = nodes[u].children;
  nodes[u].children = t;
}
void linearize(int u) {
  int c_idx = ++l_ptr;
  nodes[u].l_idx = c_idx;
  linearized_tree[c_idx].animal_idx = u;
  struct E *t = nodes[u].children;
  while (t) {
    linearize(t->v);
    t = t->next;
  }
  linearized_tree[c_idx].until = l_ptr;
}
int getBlockNumber(int idx) { return (idx - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(l_ptr, block_size * blk_id); }
void removeDirtiness(int blk_id) {
  if (blocks[blk_id].dirty != 0) {
    int blk_l, blk_r;
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    blocks[blk_id].sum = 0;
    for (int i = blk_l; i <= blk_r; ++i) {
      vps_coverage[i] += blocks[blk_id].dirty;
      if (vps_coverage[i] == 0)
        blocks[blk_id].sum += nodes[linearized_tree[i].animal_idx].animals;
    }
    blocks[blk_id].dirty = 0;
  }
}
void updateRange(int l, int r, int val) {
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    if (l == blk_l && blk_r <= r) {
      blocks[blk_id].dirty += val;
      l = blk_r + 1;
    } else {
      removeDirtiness(blk_id);
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i) {
        if (vps_coverage[i] == 1 && val == -1)
          blocks[blk_id].sum += nodes[linearized_tree[i].animal_idx].animals;
        else if (vps_coverage[i] == 0 && val == 1)
          blocks[blk_id].sum -= nodes[linearized_tree[i].animal_idx].animals;
        vps_coverage[i] += val;
      }
      l = t_r + 1;
    }
  }
}
void toggleVPS(int u) {
  int l, r, val;
  if (nodes[u].vps) val = -1;
  else val = 1;
  l = nodes[u].l_idx;
  r = linearized_tree[l].until;
  updateRange(l, r, val);
  nodes[u].vps = !nodes[u].vps;
}
ll getSum(int u) {
  int l = nodes[u].l_idx, r = linearized_tree[l].until;
  int blk_id, blk_l, blk_r;
  ll sum = 0;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    if (l == blk_l && blk_r <= r) {
      if (blocks[blk_id].dirty < 0) {
        removeDirtiness(blk_id);
        sum += blocks[blk_id].sum;
      } else if (blocks[blk_id].dirty == 0)
        sum += blocks[blk_id].sum;
      l = blk_r + 1;
    } else {
      removeDirtiness(blk_id);
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i)
        if (vps_coverage[i] == 0)
          sum += nodes[linearized_tree[i].animal_idx].animals;
      l = t_r + 1;
    }
  }
  return sum;
}
void preprocess() {
  int t_r = getBlockNumber(l_ptr);
  int blk_l, blk_r;
  for (int blk_id = 1; blk_id <= t_r; ++blk_id) {
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    for (int i = blk_l; i <= blk_r; ++i)
      blocks[blk_id].sum += nodes[linearized_tree[i].animal_idx].animals;
  }
}
void program() {
  int u, v, q;
  scanf("%d", &n);
  block_size = sqrt(n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &nodes[i].animals);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d", &u, &v);
    addToEdges(u, v);
  }
  linearize(1);
  preprocess();
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &u, &v);
    switch (u) {
      case 1:
        toggleVPS(v);
        break;
      case 2:
        printf("%lld\n", getSum(v));
        break;
    }
  }
}
int main() {
  program();
  return 0;
}
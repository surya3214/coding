// AC Square Root Decomposition
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define BLOCKS_MAX 317
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int h[BUFF(N_MAX)];
int n, k;
struct {
  int time;
  bool set;
  int max_val, min_val;
  int blk_l, blk_r;
} blocks[BUFF(BLOCKS_MAX)];
struct {
  int max_val, min_val;
} blocksInRange[BUFF(BLOCKS_MAX)][BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
int t_time;
void reset() {
  ++t_time;
  block_size = ceil(sqrt(n));
  block_count = getBlockNumber(n);
}
void sanitizeBlock(int blk_id) {
  if (blocks[blk_id].time != t_time) {
    blocks[blk_id].set = false;
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
    blocks[blk_id].time = t_time;
  }
}
void addToBlocks(int blk_id, int val) {
  if (blocks[blk_id].set) {
    blocks[blk_id].max_val = max(blocks[blk_id].max_val, val);
    blocks[blk_id].min_val = min(blocks[blk_id].min_val, val);
  } else {
    blocks[blk_id].min_val = blocks[blk_id].max_val = val;
    blocks[blk_id].set = true;
  }
}
void getMaxMinFromBlocks(int l, int r, int &t_max, int &t_min) {
  t_max = h[l], t_min = h[l];
  int blk_a, blk_b;
  blk_a = getBlockNumber(l) + 1;
  blk_b = getBlockNumber(r) - 1;
  if (blk_a <= blk_b) {
    t_max = max(t_max, blocksInRange[blk_a][blk_b].max_val);
    t_min = min(t_min, blocksInRange[blk_a][blk_b].min_val);
  }
  int t_r = min(r, blocks[blk_a - 1].blk_r);
  while (l <= t_r) {
    t_max = max(t_max, h[l]);
    t_min = min(t_min, h[l]);
    ++l;
  }
  l = max(l, blocks[blk_b + 1].blk_l);
  while (l <= r) {
    t_max = max(t_max, h[l]);
    t_min = min(t_min, h[l]);
    ++l;
  }
}
int t_abs(int x) { return x > 0 ? x : -x; }
int compute() {
  int ret = t_abs(h[2] - h[1]);
  int t_max, t_min;
  for (int i = 1; i <= n - 1; ++i) {
    getMaxMinFromBlocks(i + 1, min(n, i + k + 1), t_max, t_min);
    ret = max(ret, t_abs(h[i] - t_max));
    ret = max(ret, t_abs(h[i] - t_min));
  }
  return ret;
}
void computeRange() {
  int t_max, t_min;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    t_max = blocks[blk_id].max_val;
    t_min = blocks[blk_id].min_val;
    for (int b_id = blk_id; b_id <= block_count; ++b_id) {
      t_max = max(t_max, blocks[b_id].max_val);
      t_min = min(t_min, blocks[b_id].min_val);
      blocksInRange[blk_id][b_id].max_val = t_max;
      blocksInRange[blk_id][b_id].min_val = t_min;
    }
  }
}
void program() {
  int tcase, blk_id, blk_r;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &k);
    reset();
    blk_id = 1;
    sanitizeBlock(blk_id);
    blk_r = blocks[blk_id].blk_r;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &h[i]);
      addToBlocks(blk_id, h[i]);
      if (i == blk_r) {
        ++blk_id;
        sanitizeBlock(blk_id);
        blk_r = blocks[blk_id].blk_r;
      }
    }
    computeRange();
    printf("%d\n", compute());
  }
}
int main() {
  program();
  return 0;
}
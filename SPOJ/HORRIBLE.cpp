// AC Square Root Decomposition
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define BLOCKS_MAX 317
#define BLOCKS_SIZE 317
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  ll sum;
  ll dirty;
  int time, blk_l, blk_r;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(N_MAX, blk_id * block_size); }
ll numbers[BUFF(N_MAX)];
int n, q, t_time;
void reset() { ++t_time; }
void sanitizeBlock(int blk_id) {
  if (blocks[blk_id].time != t_time) {
    for (int i = blocks[blk_id].blk_l; i <= blocks[blk_id].blk_r; ++i)
      numbers[i] = 0;
    blocks[blk_id].sum = blocks[blk_id].dirty = 0;
    blocks[blk_id].time = t_time;
  }
}
void removeDirtiness(int blk_id) {
  if (blocks[blk_id].dirty) {
    for (int i = blocks[blk_id].blk_l; i <= blocks[blk_id].blk_r; ++i)
      numbers[i] += blocks[blk_id].dirty;
    blocks[blk_id].dirty = 0;
  }
}
void addNumber(int l, int r, int val) {
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    sanitizeBlock(blk_id);
    if (l == blk_l && blk_r <= r) {
      blocks[blk_id].sum += (1LL * val * (blk_r - blk_l + 1));
      blocks[blk_id].dirty += val;
      l = blk_r + 1;
    } else {
      removeDirtiness(blk_id);
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i)
        numbers[i] += val;
      blocks[blk_id].sum += (1LL * val * (t_r - l + 1));
      l = t_r + 1;
    }
  }
}
ll getSumIn(int l, int r) {
  int blk_id, blk_l, blk_r;
  ll ret = 0;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    sanitizeBlock(blk_id);
    if (l == blk_l && blk_r <= r) {
      ret += blocks[blk_id].sum;
      l = blk_r + 1;
    } else {
      removeDirtiness(blk_id);
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i)
        ret += numbers[i];
      l = t_r + 1;
    }
  }
  return ret;
}
void ready() {
  block_size = BLOCKS_SIZE;
  for (int blk_id = 1; blk_id <= BLOCKS_MAX; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
  }
}
void program() {
  int tcase, type, l, r, val;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= q; ++i) {
      scanf("%d %d %d", &type, &l, &r);
      if (!type) {
        scanf("%d", &val);
        addNumber(l, r, val);
      } else printf("%lld\n", getSumIn(l, r));
    }
  }
}
int main() {
  ready();
  program();
  return 0;
}
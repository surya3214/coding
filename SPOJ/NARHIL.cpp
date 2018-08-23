// AC - Square Root Decomposition, sqrt(n) gives TLE
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define BLOCKS_SIZE 100
#define BLOCKS_MAX 1000
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct {
  int a, h;
} hills[BUFF(N_MAX)];
struct {
  bool set;
  ll val;
  int height;
} ans;
struct {
  int sum;
  int dirty;
  int time;
  int blk_l, blk_r;
  ll b_sum;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count, block_start;
struct {
  int time;
  int cnt;
} hills_h[BUFF(N_MAX)];
int b_time;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(N_MAX, blk_id * block_size); }
void reset() {
  ans.set = false;
  ans.val = -1;
  ++b_time;
}
int t_abs(int x) { return x > 0 ? x : -x; }
void updateAns(ll val, int height) {
  if (!ans.set) {
    ans.height = height;
    ans.val = val;
    ans.set = true;
  } else if (val < ans.val) {
    ans.val = val;
    ans.height = height;
  }
}
void sanitizeBlock(int blk_id) {
  if (blocks[blk_id].time != b_time) {
    blocks[blk_id].dirty = blocks[blk_id].sum = blocks[blk_id].b_sum = 0;
    blocks[blk_id].time = b_time;
  }
}
void sanitizeHillsH(int i) {
  if (hills_h[i].time != b_time) {
    hills_h[i].cnt = 0;
    hills_h[i].time = b_time;
  }
}
ll findHillsHigherThan(int l) {
  int r = N_MAX;
  ll cnt = 0;
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    sanitizeBlock(blk_id);
    if (l == blk_l && blk_r <= r) {
      cnt += blocks[blk_id].b_sum;
      break;
    } else {
      int t_r;
      t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i) {
        sanitizeHillsH(i);
        cnt += hills_h[i].cnt + blocks[blk_id].dirty;
      }
      l = t_r + 1;
    }
  }
  return cnt;
}
void addToBlocks(int r) {
  int l = hills[n].h + 1;
  int blk_id, blk_l, blk_r, t_r;
  for (int blk_id = getBlockNumber(r); blk_id >= block_start; --blk_id) {
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    sanitizeBlock(blk_id);
    if (l <= blk_l && blk_r <= r) {
      ++blocks[blk_id].dirty;
      blocks[blk_id].sum += (blk_r - blk_l + 1);
    } else if (l >= blk_l && l <= blk_r) {
      t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i) {
        sanitizeHillsH(i);
        ++hills_h[i].cnt;
        ++blocks[blk_id].sum;
      }
    } else if (r >= blk_l && r <= blk_r) {
      for (int i = blk_l; i <= r; ++i) {
        sanitizeHillsH(i);
        ++hills_h[i].cnt;
        ++blocks[blk_id].sum;
      }
    }
    sanitizeBlock(blk_id + 1);
    blocks[blk_id].b_sum = blocks[blk_id].sum + blocks[blk_id + 1].b_sum;
  }
}
void compute() {
  for (int i = n - 1; i >= 1; --i) {
    if (hills[i].h >= hills[n].h) { // can possibly see the peak of nth hill from here
      updateAns(2 * t_abs(hills[1].a - hills[i].a) + findHillsHigherThan(hills[i].h + 1), hills[i].h);
      addToBlocks(hills[i].h);
    }
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  block_size = BLOCKS_SIZE;
  block_count = BLOCKS_MAX;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
  }
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &hills[i].a);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &hills[i].h);
    block_start = getBlockNumber(hills[n].h);
    compute();
    printf("%lld\n", ans.val);
  }
}
int main() {
  program();
  return 0;
}
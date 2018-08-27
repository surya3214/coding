// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 300000
#define BLOCKS_MAX 548
#define BLOCKS_SIZE 548
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, d;
int threshold[BUFF(N_MAX)];
int until[BUFF(N_MAX)];
struct T {
  int idx;
  int val;
} sorted_t[BUFF(N_MAX)];
int dp[BUFF(N_MAX)];
struct {
  int max_idx;
  int min_val;
  int time;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count, b_time;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
bool m_comparator(T a, T b) {
  if (a.val != b.val)
    return a.val < b.val;
  return a.idx < b.idx;
}
void resetBlocks() { ++b_time; }
void sanitizeBlock(int blk_id) {
  if (blocks[blk_id].time != b_time) {
    blocks[blk_id].max_idx = 0;
    blocks[blk_id].max_idx = N_MAX;
    blocks[blk_id].time = b_time;
  }
}
void addToBlocks(int blk_id, int val) {
  sanitizeBlock(blk_id);
  blocks[blk_id].max_idx = max(blocks[blk_id].max_idx, val);
  blocks[blk_id].min_val = min(blocks[blk_id].min_val, val);
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int findLowerBound(int val) { // returns the first index x in sorted_t where sorted_t[x] >= val
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (sorted_t[mid].val >= val)
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
int findHigherBound(int val) {
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (sorted_t[mid].val <= val)
      l = mid + 1;
    else r = mid - 1;
  }
  return l - 1;
}
int findGreaterThanXIn(int l, int r, int x) {
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    if (l == blk_l && blocks[blk_id].max_idx < x)
      l = blk_r + 1;
    else {
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i)
        if (sorted_t[i].idx >= x)
          return i;
      l = t_r + 1;
    }
  }
  return l;
}
int findMinIn(int l, int r) {
  int ret = n;
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    if (l == blk_l && blk_r <= r) {
      ret = min(ret, blocks[blk_id].min_val);
      l = blk_r + 1;
    } else {
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i)
        ret = min(ret, dp[i]);
      l = blk_r + 1;
    }
  }
  return ret;
}
int compute() {
  resetBlocks();
  // compute their ranges
  int blk_id = 1, blk_until;
  blk_until = getBlockRight(blk_id);
  for (int i = 1; i <= n; ++i) {
    if (i > blk_until) {
      ++blk_id;
      blk_until = getBlockRight(blk_id);
    }
    addToBlocks(blk_id, sorted_t[i].idx);
  }
  int a, b, ret, x;
  for (int i = 1; i <= n; ++i) {
    x = threshold[i] + d + 1;
    a = findLowerBound(x);
    if (a == n + 1) a = n;
    else a = findGreaterThanXIn(a, n, i + 1) - 1;
    x = threshold[i] - d - 1;
    b = findHigherBound(x);
    if (b == n + 1) b = n;
    else b = findGreaterThanXIn(1, b, i + 1) - 1;
    until[i] = min(a, b);
  }
  resetBlocks();
  dp[n] = 0;
  addToBlocks(getBlockNumber(n), 0);
  blk_id = getBlockNumber(n - 1);
  blk_until = getBlockLeft(blk_id);
  for (int i = n - 1; i >= 1; --i) {
    if (blk_until > i) {
      --blk_id;
      blk_until = getBlockLeft(blk_id);
    }
    dp[i] = 1 + findMinIn(min(n, i + 1), min(n, until[i + 1]));
    addToBlocks(blk_id, dp[i]);
  }
  return 1 + findMinIn(min(n, 2), min(n, until[1]));
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &d);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &threshold[i]);
      sorted_t[i].idx = i;
      sorted_t[i].val = threshold[i];
    }
    sort(sorted_t + 1, sorted_t + 1 + n, m_comparator);
    printf("%d\n", compute());
  }
}
void ready() {
  block_size = BLOCKS_SIZE;
  block_count = getBlockNumber(N_MAX);
}
int main() {
  ready();
  program();
  return 0;
}
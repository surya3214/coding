// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#pragma GCC optimize "O3"
#define N_MAX 100000
#define BLOCKS_MAX 317
#define BLOCKS_SIZE 317
using namespace std;
typedef long long int ll;
int n, q;
struct {
  int val;
  int s, e;
} input[BUFF(N_MAX)];
struct {
  int val;
  int time;
} blocks[BUFF(BLOCKS_MAX)];
int b_time;
int block_size, block_count;
int getSquareRootOf(int x) {
  int i = 2;
  while (i * i <= x) ++i;
  return --i;
}
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
void setBlockValue(int blk_id, int val) {
  if (blocks[blk_id].time != b_time) {
    blocks[blk_id].val = val;
    blocks[blk_id].time = b_time;
  } else blocks[blk_id].val = max(blocks[blk_id].val, val);
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int findLowerBound(int x) {
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (input[mid].val >= x)
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
int findUpperBound(int x) {
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (input[mid].val <= x)
      l = mid + 1;
    else r = mid - 1;
  }
  return l - 1;
}
void process() {
  int l, r;
  l = 1, r = n;
  int t_l, t_r, s, e;
  while (l <= r) {
    t_l = findLowerBound(input[l].val);
    t_r = findUpperBound(input[l].val);
    for (int i = t_l; i <= t_r; ++i)
      input[i].s = t_l, input[i].e = t_r;
    l = t_r + 1;
  }
}
int findMaxCount(int l, int r) {
  int blk_id, blk_l, blk_r;
  int t_l = l, t_r;
  int ans = 1;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    if (l == blk_l && blk_r <= r) {
      ans = max(ans, blocks[blk_id].val);
      ans = max(ans, min(r, input[blk_l].e) - max(t_l, input[blk_l].s) + 1);
      ans = max(ans, min(r, input[blk_r].e) - max(t_l, input[blk_r].s) + 1);
      l = blk_r + 1;
    } else {
      t_r = min(r, blk_r);
      while (l <= t_r) {
        ans = max(ans, min(r, input[l].e) - max(t_l, input[l].s) + 1);
        l = input[l].e + 1;
      }
    }
  }
  return ans;
}
void reset() {
  ++b_time;
  block_size = BLOCKS_SIZE;
  block_size = getSquareRootOf(n);
  block_count = getBlockNumber(n);
}
void program() {
  scanf("%d", &n);
  while (n != 0) {
    reset();
    scanf("%d", &q);
    int blk_id, blk_r, idx;
    blk_id = blk_r = idx = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &input[i].val);
      if (i > blk_r || input[i].val != input[idx].val) {
        setBlockValue(blk_id, i - idx);
        idx = i;
        if (i > blk_r) {
          ++blk_id;
          blk_r = getBlockRight(blk_id);
        }
      }
    }
    setBlockValue(blk_id, n + 1 - idx);
    process();
    int l, r;
    for (int i = 1; i <= q; ++i) {
      scanf("%d %d", &l, &r);
      printf("%d\n", findMaxCount(l, r));
    }
    scanf("%d", &n);
  }
}
int main() {
  program();
  return 0;
}
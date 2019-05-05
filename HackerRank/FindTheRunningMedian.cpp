// AC Square Root Decomposition, Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX (int) 1e5
#define BLOCKS_MAX 317
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, cnt[BUFF(VAL_MAX)];
struct B {
  int blk_l, blk_r, blk_cnt;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(VAL_MAX, blk_id * block_size); }
void process() {
  int blk_id = getBlockNumber(n);
  ++cnt[n];
  ++blocks[blk_id].blk_cnt;
}
int findNth(int k) {
  int ret = -1;
  for (int blk_id = 1; blk_id <= block_count && ret == -1; ++blk_id) {
    if ((k - blocks[blk_id].blk_cnt) > 0)
      k -= blocks[blk_id].blk_cnt;
    else {
      for (int x = blocks[blk_id].blk_l; x <= blocks[blk_id].blk_r; ++x) {
        if (k - cnt[x] > 0)
          k -= cnt[x];
        else {
          ret = x;
          break;
        }
      }
    }
  }
  return ret;
}
void program() {
  int tcase;
  float ans;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d", &n);
    process();
    ans = findNth(t / 2 + 1);
    if (!(t & 1)) {
      ans += findNth(t / 2);
      ans /= 2;
    }
    printf("%.1f\n", ans);
  }
}
void readyUp() {
  block_size = block_count = BLOCKS_MAX;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
  }
}
int main() {
  readyUp();
  program();
  return 0;
}
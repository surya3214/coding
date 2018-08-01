// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#pragma GCC optimize "O3"
#define N_MAX 50000
#define BLOCKS_MAX 225
#define BLOCKS_SIZE 225
#define INF 1e9
using namespace std;
int n;
int input[BUFF(N_MAX)];
struct {
  int best_in_range;
  int best_from_left;
  int best_from_right;
  int total_sum;
} buffer;
struct {
  int best_in_range;
  int best_from_left;
  int best_from_right;
  int total_sum;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
int getSquareRootOf(int x) {
  int i = 2;
  while (i * i <= x) ++i;
  return --i;
}
void assessRange(int l, int r) {
  int t_l, t_r, sum, sum_p;
  buffer.total_sum = 0;
  buffer.best_in_range = buffer.best_from_left = input[l];
  buffer.best_from_right = input[r];
  t_l = t_r = sum = 0;
  sum_p = l;
  for (int i = l; i <= r; ++i) {
    buffer.best_in_range = max(buffer.best_in_range, input[i]);
    sum += input[i];
    while (sum < 0)
      sum -= input[sum_p++];
    if (sum_p <= i)
      buffer.best_in_range = max(buffer.best_in_range, sum);
    buffer.total_sum += input[i];
    t_l += input[i];
    buffer.best_from_left = max(buffer.best_from_left, t_l);
  }
  for (int i = r; i >= l; --i) {
    t_r += input[i];
    buffer.best_from_right = max(buffer.best_from_right, t_r);
  }
}
void setBlockValue(int blk_id) {
  blocks[blk_id].best_in_range = buffer.best_in_range;
  blocks[blk_id].best_from_left = buffer.best_from_left;
  blocks[blk_id].best_from_right = buffer.best_from_right;
  blocks[blk_id].total_sum = buffer.total_sum;
}
void process() {
  block_size = BLOCKS_SIZE;
  block_count = getBlockNumber(n);
  int blk_l, blk_r;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    assessRange(blk_l, blk_r);
    setBlockValue(blk_id);
  }
}
int findMax(int l, int r) {
  int ans = input[l];
  struct {
    bool set;
    int val;
  } cont;
  cont.set = false;
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    if (l == blk_l && blk_r <= r) {
      ans = max(ans, blocks[blk_id].best_in_range);
      if (cont.set)
        ans = max(ans, cont.val + blocks[blk_id].best_from_left);
      if (cont.set)
        cont.val = max(cont.val + blocks[blk_id].total_sum, blocks[blk_id].best_from_right);
      else {
        cont.val = blocks[blk_id].best_from_right;
        cont.set = true;
      }
      ans = max(ans, cont.val);
      l = blk_r + 1;
    } else {
      int t_r = min(r, blk_r);
      assessRange(l, t_r);
      ans = max(ans, buffer.best_in_range);
      if (cont.set)
        ans = max(ans, cont.val + buffer.best_from_left);
      if (cont.set)
        cont.val = max(cont.val + buffer.total_sum, buffer.best_from_right);
      else {
        cont.val = buffer.best_from_right;
        cont.set = true;
      }
      ans = max(ans, cont.val);
      l = t_r + 1;
    }
  }
  return ans;
}
void program() {
  int q, l, r;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%intd", &input[i]);
  process();
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &l, &r);
    printf("%d\n", findMax(l, r));
  }
}
int main() {
  program();
  return 0;
}
// AC Similar to LIS Ayyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 200000
#define BLOCKS_MAX 448
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct Q {
  bool type;
  int idx, val;
} queries[BUFF(2 * N_MAX)];
int q_ptr;
int c[BUFF(N_MAX)];
int n, m, ans;
int lcs[BUFF(N_MAX)];
struct {
  bool inited;
  int max_val;
  int blk_l, blk_r;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
void insert(int idx, int val, bool type) {
  ++q_ptr;
  queries[q_ptr].idx = idx;
  queries[q_ptr].val = val;
  queries[q_ptr].type = type;
}
bool q_comparator(Q a, Q b) {
  if (a.val != b.val)
    return a.val < b.val;
  else if (a.type != b.type)
    return a.type < b.type;
  return a.idx < b.idx;
}
void convert() {
  int l, r, t_r;
  l = 1;
  t_r = n + m;
  ans = t_r;
  while (l <= t_r) {
    r = l + 1;
    if (!queries[l].type) {
      while (r <= t_r && !queries[r].type && queries[r].val == queries[l].val)
        ++r;
      while (r <= t_r && queries[r].type && queries[r].val == queries[l].val) {
        c[queries[r].idx] = queries[l].idx;
        --ans;
        ++l;
        ++r;
      }
    }
    l = r;
  }
}
void initBlock(int blk_id) {
  if (!blocks[blk_id].inited) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
    blocks[blk_id].inited = true;
  }
}
int findMax(int l) {
  int ret = 0;
  int blk_id, blk_l, blk_r;
  while (l <= n) {
    blk_id = getBlockNumber(l);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    if (l == blk_l) {
      ret = max(ret, blocks[blk_id].max_val);
      l = n + 1;
    } else {
      int t_r = min(n, blk_r);
      for (int i = l; i <= t_r; ++i)
        ret = max(ret, lcs[i]);
      l = t_r + 1;
    }
  }
  return ret;
}
void update(int idx, int val) {
  for (int blk_id = getBlockNumber(idx); blk_id >= 1; --blk_id)
    blocks[blk_id].max_val = max(blocks[blk_id].max_val, val);
}
int findLCS() {
  int ret = 0;
  for (int i = m; i >= 1; --i) {
    if (c[i]) { // c[i] is the index
      lcs[c[i]] = 1 + findMax(c[i] + 1);
      update(c[i], lcs[c[i]]);
      ret = max(ret, lcs[c[i]]);
    }
  }
  return ret;
}
void initBlocks() {
  for (int blk_id = 1; blk_id <= getBlockNumber(n); ++blk_id)
    initBlock(blk_id);
}
void program() {
  int x;
  scanf("%d %d", &n, &m);
  block_size = sqrt(n);
  initBlocks();
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    insert(i, x, false);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &x);
    insert(i, x, true);
  }
  sort(queries + 1, queries + 1 + q_ptr, q_comparator);
  convert();
  printf("%d\n", ans - findLCS());
}
int main() {
  program();
  return 0;
}
// TLE - Should use radix sort
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (2 * 1e7)
#define VAL_MAX (int) (1e9 + 7)
#define MOD (int) (1e9 + 7)
#define BLOCKS_MAX 100000 // 31623
#define BLOCKS_SIZE 10000 // 31623
#define VAL_MAX_IN_S_BLOCK 178
// #pragma GCC optimize "Ofast"
using namespace std;
typedef long long int ll;
int t_time;
int n, a, b;
ll ans;
struct L {
  int val;
  struct L *next;
} l_nodes_pool[BUFF(N_MAX)];
int l_pool_ptr;
struct {
  int time;
  struct L *q; // keeps a list of the localised element indices that have been visited currently
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
void reset() {
  ++t_time;
  ans = l_pool_ptr = 0;
}
void m_mod(ll &t) {
  t %= MOD;
}
int getBlockNumber(int idx) { return (idx - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(VAL_MAX, blk_id * block_size); }
void sanitizeBlock(int blk_id) {
  if (blocks[blk_id].time != t_time) {
    blocks[blk_id].q = NULL;
    blocks[blk_id].time = t_time;
  }
}
struct L *getLNodesFromPool() { return &l_nodes_pool[l_pool_ptr++]; }
void addToAccessed(int blk_id, int idx) {
  sanitizeBlock(blk_id);
  struct L *t = getLNodesFromPool();
  t->val = idx;
  t->next = blocks[blk_id].q;
  blocks[blk_id].q = t;
}
void addToBlocks(int val) {
  int blk_id = getBlockNumber(val);
  int blk_l = getBlockLeft(blk_id);
  int idx = val - blk_l + 1;
  addToAccessed(blk_id, idx);
}
struct {
  int time;
  int count;
} s_blocks[BUFF(BLOCKS_MAX)];
struct {
  int time;
} s_blocks_accessed[BUFF(VAL_MAX_IN_S_BLOCK)];
int s_time;
void sanitizeSBlock(int idx) {
  if (s_blocks[idx].time != s_time) {
    s_blocks[idx].count = 0;
    s_blocks[idx].time = s_time;
  }
}
int getSBlockNumber(int idx) {
  return (idx - 1) / VAL_MAX_IN_S_BLOCK  + 1;
}
void addToSBlocks(int idx) {
  sanitizeSBlock(idx);
  ++s_blocks[idx].count;
  s_blocks_accessed[getSBlockNumber(idx)].time = s_time;
}
void resetSBlocks() { ++s_time; }
void compute() {
  int l, r, s_blk;
  block_count = getBlockNumber(VAL_MAX);
  int base, cnt, seen, l_cur;
  seen = 0;
  struct L *t;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    sanitizeBlock(blk_id);
    base = getBlockLeft(blk_id) - 1;
    if (!blocks[blk_id].q) continue;
    t = blocks[blk_id].q;
    resetSBlocks();
    while (t) {
      addToSBlocks(t->val);
      t = t->next;
    }
    for (int s_blk_id = 1; s_blk_id <= VAL_MAX_IN_S_BLOCK; ++s_blk_id) {
      if (s_blocks_accessed[s_blk_id].time == s_time) {
        l = ((s_blk_id - 1) * VAL_MAX_IN_S_BLOCK) + 1;
        r = min(BLOCKS_MAX, s_blk_id * VAL_MAX_IN_S_BLOCK);
        for (int i = l; i <= r; ++i) {
          sanitizeSBlock(i);
          l_cur = i;
          while (s_blocks[i].count) {
            ++seen;
            ans = (ans + 1LL * seen * (base + l_cur)) % MOD;
            m_mod(ans);
            --s_blocks[i].count;
          }
        }
      }
    }
  }
}
void program() {
  int tcase;
  ll ret;
  scanf("%d", &tcase);
  block_size = BLOCKS_SIZE;
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d %d %lld", &n, &a, &b, &ret);
    addToBlocks(ret);
    for (int i = 2; i <= n; ++i) {
      ret = ((ret * a) + b) % MOD;
      m_mod(ret);
      addToBlocks(ret);
    }
    compute();
    printf("%lld\n", ans);
  }
}
int main() {
  freopen("ADATOMAT_input.txt", "r", stdin);
  program();
  return 0;
}

/*
1
20000000 5 6 7
*/
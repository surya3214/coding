// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100000
#define BLOCKS_MAX 317
#define ALPHA_CHARS_MAX 26
#define MOD (int) (1e9 + 7)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int fact[BUFF(LEN_MAX)];
char str[BUFF(LEN_MAX)];
int n;
struct {
  int freq[BUFF(ALPHA_CHARS_MAX)];
  int blk_l, blk_r;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
int getIndexFromChar(char x) { return x - 'a' + 1; }
void initBlocks() {
  int x;
  block_size = ceil(sqrt(n));
  block_count = getBlockNumber(n);
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
    for (int i = blocks[blk_id].blk_l; i <= blocks[blk_id].blk_r; ++i) {
      x = getIndexFromChar(str[i - 1]);
      ++blocks[blk_id].freq[x];
    }
  }
}
int t_freq[BUFF(ALPHA_CHARS_MAX)];
int getCount(int l, int r) {
  int even_cnt, odd_cnt, x, diffs;
  even_cnt = odd_cnt = diffs = 0;
  int blk_id, blk_l, blk_r;
  for (int i = 1; i <= ALPHA_CHARS_MAX; ++i)
    t_freq[i] = 0;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    if (l == blk_l && blk_r <= r) {
      for (int i = 1; i <= ALPHA_CHARS_MAX; ++i) {
        t_freq[i] += blocks[blk_id].freq[i];
      }
      l = blk_r + 1;
    } else {
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i) {
        x = getIndexFromChar(str[i - 1]);
        ++t_freq[x];
      }
      l = t_r + 1;
    }
  }
  for (int i = 1; i <= ALPHA_CHARS_MAX; ++i) {
    if (t_freq[i]) ++diffs;
    if (t_freq[i] % 2) ++odd_cnt;
    even_cnt += t_freq[i] / 2;
  }
  if (diffs == 1)
    return 1;
  ll ret = (max(1, odd_cnt) * 1LL * fact[even_cnt]) % MOD;
  return ret;
}
void program() {
  scanf("%s", str);
  for (n = 0; str[n]; ++n);
  initBlocks();
  int q, l, r;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &l, &r);
    printf("%d\n", getCount(l, r));
  }
}
void ready() {
  ll ret;
  fact[0] = 1;
  for (int i = 1; i <= LEN_MAX; ++i) {
    ret = (i * 1LL * fact[i - 1]) % MOD;
    fact[i] = ret;
  }
}
int main() {
  freopen("input.txt", "r", stdin);
  ready();
  program();
  return 0;
}
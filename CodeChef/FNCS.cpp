// AC - Square Root Decomposition based block sum precomputation, BIT
#include <bits/stdc++.h>
#define N_MAX 100010
#define BLOCKS_MAX 500
using namespace std;
typedef unsigned long long int ull;
int n, block_size, block_count;
ull BIT[N_MAX]; // used to query the original Ai
ull block_sum[BLOCKS_MAX];
ull a[N_MAX];
int occurences[BLOCKS_MAX][N_MAX];
int getBlockNumber(int i) { return ((i - 1) / block_size) + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
struct {
  int l, r;
} functions[N_MAX];
void insertIntoBIT(int idx, ull val) {
  while (idx <= n) {
    BIT[idx] += val;
    idx = idx + (idx & -idx);
  }
}
ull queryBIT(int idx) {
  ull sum = 0;
  while (idx > 0) {
    sum += BIT[idx];
    idx = idx - (idx & -idx);
  }
  return sum;
}
void process(int i) {
  int blk_id = getBlockNumber(i);
  occurences[blk_id][functions[i].l]++;
  occurences[blk_id][functions[i].r + 1]--;
  ull sum = queryBIT(functions[i].r) - queryBIT(functions[i].l - 1);
  block_sum[blk_id] += sum;
}
ull solve(int l, int r) {
  int blk_l, blk_l_s, blk_l_e, t_r;
  ull sum = 0;
  while (l <= r) {
    blk_l = getBlockNumber(l);
    blk_l_s = getBlockLeft(blk_l);
    blk_l_e = getBlockRight(blk_l);
    if (l == blk_l_s && blk_l_e <= r) {
      sum += block_sum[blk_l];
      l = blk_l_e + 1;
    } else {
      t_r = min(r, blk_l_e);
      while (l <= t_r) {
        sum += queryBIT(functions[l].r) - queryBIT(functions[l].l - 1);
        l++;
      }
    }
  }
  return sum;
}
void update(int idx, ull new_val) {
  ull prev_val = a[idx], diff = new_val - prev_val;
  insertIntoBIT(idx, diff);
  for (int blk = 1; blk <= block_count; blk++)
    block_sum[blk] += occurences[blk][idx] * diff;
  a[idx] = new_val;
}
void program() {
  int q, l, r, type;
  scanf("%d", &n);
  block_size = ceil(sqrt(n));
  block_count = getBlockNumber(n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    insertIntoBIT(i, a[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &functions[i].l, &functions[i].r);
    process(i);
  }
  for (int blk = 1; blk <= block_count; blk++)
    for (int i = 1; i <= n; i++)
      occurences[blk][i] += occurences[blk][i - 1];
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    scanf("%d %d %d", &type, &l, &r);
    if (type == 1) update(l, r);
    else if (type == 2) printf("%llu\n", solve(l, r));
  }
}
int main() {
  program();
  return 0;
}
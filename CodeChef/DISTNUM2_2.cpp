// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define EACH_SET_MAX 60
#define SETS_MAX 1667 // N_MAX / EACH_SET_MAX
// #define BLOCKS_MAX 317
#define BLOCKS_MAX 317
#define BLOCKS_SIZE 500
using namespace std;
typedef long long int ll;
int n, q, k;
struct E {
  int value;
  int index;
} elements[BUFF(N_MAX)]; // will be sorted as per its values
int reverse_map[BUFF(N_MAX)];
struct {
  int elements[BUFF(N_MAX)]; // after compression, this will represent the values in the original array
  int total_count;
} compression;
ll ans;
struct B {
  // structure represents the numbers of range [1 - 10^5] present in a range
  ll sets[BUFF(SETS_MAX)]; // sets[1] -> [1 - 60], sets[2] -> [61 - 120], sets[1666] -> [999961 - 100000]
} blocks[BUFF(BLOCKS_MAX)], blocksRange[BUFF(BLOCKS_MAX)][BUFF(BLOCKS_MAX)], b;
int block_size, block_count;
int getBlockNumber(int idx) { return (idx - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
void compress() {
  int *ptr = &compression.total_count;
  *ptr = 0; // compressed value
  for (int i = 1; i <= n; i++) {
    if (elements[i].value != elements[i - 1].value) { // new number
      (*ptr)++;
      reverse_map[*ptr] = elements[i].value;
    }
    compression.elements[elements[i].index] = *ptr;
  }
}
int getSquareRoot(int x) {
  int i = 1;
  while (i * i <= x)
    i++;
  return i - 1;
}
int getSetNumber(int value) { // returns 1 for value[1-60], 2 for [61-120], ...
  return ((value - 1) / EACH_SET_MAX) + 1;
}
void setBitInBlock(int blk_id, int value) {
  ll *p = blocks[blk_id].sets;
  int set_id = getSetNumber(value);
  value -= ((set_id - 1) * EACH_SET_MAX); // localise the value to its set block position
  p[set_id] = p[set_id] | (1LL << (value - 1));
}
void blockify() { // construct set_bit for each bit
  block_size = getSquareRoot(n);
  block_count = getBlockNumber(n);
  int blk, blk_l, blk_r;
  for (blk = 1; blk <= block_count; blk++) {
    blk_l = getBlockLeft(blk);
    blk_r = getBlockRight(blk);
    for (int i = blk_l; i <= blk_r; i++)
      setBitInBlock(blk, compression.elements[i]);
  }
  for (blk = 1; blk < block_count; blk++) { // combine blockRange[blk][i - 1] with block[i] to make blockRange[blk][i]
    blocksRange[blk][blk] = blocks[blk];
    for (int next_blk = blk + 1; next_blk <= block_count; next_blk++)
      for (int set_id = 1; set_id <= SETS_MAX; set_id++)
        blocksRange[blk][next_blk].sets[set_id] = blocksRange[blk][next_blk - 1].sets[set_id] | blocks[next_blk].sets[set_id];
  }
}
int my_mod(int x) {
  while (x >= n)
    x -= n;
  return x;
}
void swapIfRequired(int &l, int &r) {
  if (l > r) {
    int tmp = l;
    l = r;
    r = tmp;
  }
}
int findKth(int l, int r) {
  int l_blk, r_blk, blk_r;
  l_blk = getBlockNumber(l);
  r_blk = getBlockNumber(r);
  int value, t;
  b = blocksRange[l_blk + 1][r_blk - 1];
  blk_r = min(r, getBlockRight(l_blk));
  while (l <= blk_r) {
    value = compression.elements[l];
    t = getSetNumber(value);
    value -= ((t - 1) * EACH_SET_MAX);
    b.sets[t] |= (1LL << (value - 1));
    l++;
  }
  l = max(l, getBlockLeft(r_blk));
  while (l <= r) {
    value = compression.elements[l];
    t = getSetNumber(value);
    value -= ((t - 1) * EACH_SET_MAX);
    b.sets[t] |= (1LL << (value - 1));
    l++;
  }
  int cnt, to_be_found, pos;
  cnt = 0;
  for (int set_id = 1; set_id <= SETS_MAX; set_id++) {
    to_be_found = __builtin_popcountll(b.sets[set_id]);
    if (cnt + to_be_found < k) cnt += to_be_found;
    else { // kth number is here
      while (b.sets[set_id]) {
        pos = __builtin_ctzll(b.sets[set_id]);
        b.sets[set_id] ^= (1LL << pos);
        if (++cnt == k)
          return ((set_id - 1) * EACH_SET_MAX) + pos + 1;
      }
    }
  }
  return -1;
}
bool my_comparator(E a, E b) {
  if (a.value < b.value)
    return true;
  else return false;
}
void program() {
  int a, b, c, d, l, r;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &elements[i].value);
    elements[i].index = i;
  }
  sort(elements + 1, elements + 1 + n, my_comparator);
  compress();
  blockify();
  for (int i = 1; i <= q; i++) {
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &k);
    l = my_mod(a * max(ans, 0LL) + b) + 1;
    r = my_mod(c * max(ans, 0LL) + d) + 1;
    swapIfRequired(l, r);
    ans = findKth(l, r);
    ans = (ans != -1) ? reverse_map[ans] : ans;
    printf("%lld\n", ans);
  }
}
int main() {
  program();
  return 0;
}
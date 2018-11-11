// WA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define Q_MAX (int) (5 * 1e5)
#define BLOCKS_MAX 775
#define INF (int) 1e9
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, max_val;
int elements[BUFF(N_MAX)];
struct {
  int type;
  int idx, v;
} queries[BUFF(Q_MAX)];
struct N {
  bool type;
  int idx, val;
} numbers[BUFF(N_MAX + Q_MAX)];
int n_ptr;
int freq[BUFF(N_MAX + Q_MAX)];
int freq_sum;
struct {
  int blk_l, blk_r;
  int min_freq; // min_freq is valid iff non_zeros == (blk_r - blk_l + 1)
  int non_zeros;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(max_val, blk_id * block_size); }
bool n_comparator(N a, N b) { return a.val < b.val; }
void addToNumbers(int val, int idx, bool type) {
  ++n_ptr;
  numbers[n_ptr].val = val;
  numbers[n_ptr].idx = idx;
  numbers[n_ptr].type = type;
}
void applyCompression() {
  int num = 0;
  int diff;
  for (int i = 1; i <= n_ptr; ++i) {
    diff = numbers[i].val - numbers[i - 1].val;
    if (diff == 1)
      ++num;
    else if (diff > 1)
      num += 5;
    if (numbers[i].type)
      queries[numbers[i].idx].v = num;
    else elements[numbers[i].idx] = num;
  }
  max_val = num;
}
/*
void calculateForBlock(int blk_id) {
  blocks[blk_id].non_zeros = 0;
  blocks[blk_id].min_freq = INF;
  for (int i = blocks[blk_id].blk_l; i <= blocks[blk_id].blk_r; ++i) {
    if (freq[i]) {
      ++blocks[blk_id].non_zeros;
      blocks[blk_id].min_freq = min(blocks[blk_id].min_freq, freq[i]);
    } else {
      blocks[blk_id].min_freq = INF;
      break;
    }
  }
}
void buildBlocks() {
  block_size = ceil(sqrt(max_val));
  block_count = getBlockNumber(max_val);
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
    calculateForBlock(blk_id);
  }
}
int freqTowardsLeft(int x) {
  int ret = INF;
  int blk_id, blk_l, blk_r;
  while (x >= 1) {
    blk_id = getBlockNumber(x);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    if (x == blk_r && blocks[blk_id].non_zeros == (blk_r - blk_l + 1)) {
      ret = min(ret, blocks[blk_id].min_freq);
      x = blk_l - 1;
    } else {
      int i;
      for (i = x; i >= blk_l && freq[i]; --i)
        ret = min(ret, freq[i]);
      if (i == blk_l - 1) x = blk_l - 1;
      else break;
    }
    if (ret == 1)
      break;
  }
  return ret;
}
int freqTowardsRight(int x) {
  int ret = INF;
  int blk_id, blk_l, blk_r;
  while (x <= max_val) {
    blk_id = getBlockNumber(x);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    if (x == blk_l && blocks[blk_id].non_zeros == (blk_r - blk_l + 1)) {
      ret = min(ret, blocks[blk_id].min_freq);
      x = blk_r + 1;
    } else {
      int i;
      for (i = x; i <= blk_r && freq[i]; ++i)
        ret = min(ret, freq[i]);
      if (i == blk_r + 1) x = blk_r + 1;
      else break;
    }
    if (ret == 1)
      break;
  }
  return ret;
}
*/
int freqTowardsLeft(int x) {
  int ret = INF;
  while (x >= 1) {
    if (freq[x])
      ret = min(ret, freq[x]);
    if (!freq[x] || ret == 1)
      break;
    --x;
  }
  return ret;
}
int freqTowardsRight(int x) {
  int ret = INF;
  while (x <= max_val) {
    if (freq[x])
      ret = min(ret, freq[x]);
    if (!freq[x] || ret == 1)
      break;
    ++x;
  }
  return ret;
}
void calculateFreq() {
  for (int i = 1; i <= n; ++i)
    ++freq[elements[i]];
  int cur_min = INF;
  for (int i = 1; i <= max_val; ++i) {
    if (freq[i])
      cur_min = min(cur_min, freq[i]);
    else if (cur_min != INF) {
      freq_sum += cur_min;
      cur_min = INF;
    }
  }
  if (cur_min != INF)
    freq_sum += cur_min;
}
void reduceFrequency(int val) {
  int min_left, min_right;
  min_left = freqTowardsLeft(val - 1);
  min_right = freqTowardsRight(val + 1);
  freq_sum -= min(freq[val], min(min_left, min_right));
  --freq[val];
  if (freq[val])
    freq_sum += min(freq[val], min(min_left, min_right));
  else {
    if (min_left != INF)
      freq_sum += min_left;
    if (min_right != INF)
      freq_sum += min_right;
  }
  /*
  int blk_id = getBlockNumber(val);
  calculateForBlock(blk_id);
  */
}
void increaseFrequency(int val) {
  int min_left, min_right;
  min_left = freqTowardsLeft(val - 1);
  min_right = freqTowardsRight(val + 1);
  if (freq[val])
    freq_sum -= min(freq[val], min(min_left, min_right));
  else {
    if (min_left != INF)
      freq_sum -= min_left;
    if (min_right != INF)
      freq_sum += min_right;
  }
  ++freq[val];
  freq_sum += min(freq[val], min(min_left, min_right));
  /*
  int blk_id = getBlockNumber(val);
  calculateForBlock(blk_id);
  */
}
void program() {
  int q;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &elements[i]);
    addToNumbers(elements[i], i, false);
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &queries[i].type);
    if (queries[i].type == 1) {
      scanf("%d %d", &queries[i].idx, &queries[i].v);
      addToNumbers(queries[i].v, i, true);
    }
  }
  sort(numbers + 1, numbers + 1 + n_ptr, n_comparator);
  applyCompression();
  // buildBlocks();
  calculateFreq();
  for (int i = 1; i <= q; ++i) {
    if (queries[i].type == 1) {
      reduceFrequency(elements[queries[i].idx]);
      elements[queries[i].idx] = queries[i].v;
      increaseFrequency(elements[queries[i].idx]);
    } else printf("%d\n", freq_sum);
  }
}
int main() {
  program();
  return 0;
}
// AC Square Root Decomposition
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define BLOCKS_MAX 317
#define BLOCKS_SIZE 317
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  char type;
  int val;
} queries[BUFF(N_MAX)];
int n;
struct D {
  int val;
  int idx;
} diffs[BUFF(N_MAX)];
void addToDiffs(int val, int idx) {
  diffs[idx].val = val;
  diffs[idx].idx = idx;
}
bool d_comparator(D a, D b) { return a.val < b.val; }
int original_values[BUFF(N_MAX)];
void compressQs() {
  int l = 1, r;
  int compressed_val = 1;
  while (l <= n) {
    r = l;
    while (r + 1 <= n && diffs[r].val == diffs[r + 1].val)
      ++r;
    for (int i = l; i <= r; ++i)
      queries[diffs[i].idx].val = compressed_val;
    original_values[compressed_val] = diffs[l].val;
    ++compressed_val;
    l = r + 1;
  }
}
int total_nums_count;
int nums_count[BUFF(N_MAX)];
struct {
  int blk_l, blk_r;
  int count;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(N_MAX, blk_id * block_size); }
struct {
  bool found;
  bool sign;
  int a, b;
} ans;
int findKthFrom(int &blk_id, int &k) {
  int ret = 0;
  while (blk_id <= block_count && !ret) {
    if (blocks[blk_id].count < k) {
      k -= blocks[blk_id].count;
      ++blk_id;
    } else {
      int t_k = k;
      for (int i = blocks[blk_id].blk_l; i <= blocks[blk_id].blk_r; ++i) {
        if (nums_count[i] < t_k)
          t_k -= nums_count[i];
        else {
          ret = i;
          break;
        };
      }
    }
  }
  return ret;
}
void calculateMedian() {
  if (!total_nums_count)
    return;
  else ans.found = true;
  int median = (total_nums_count + 1) / 2;
  bool find_two = !(total_nums_count & 1);
  int a;
  int blk_id = 1;
  a = findKthFrom(blk_id, median);
  if (!find_two) {
    ans.a = original_values[a];
    ans.b = 0;
  } else {
    int b;
    ++median;
    b = findKthFrom(blk_id, median);
    ll ret = ((ll) original_values[a] + original_values[b]);
    ans.a = ret / 2;
    if (!ans.a && ret < 0)
      ans.sign = false;
    else ans.sign = true;
    ret = (ret >= 0) ? ret : -ret;
    ans.b = (ret * 10 / 2) % 10;
  }
}
void add(int val) {
  ++total_nums_count;
  ++nums_count[val];
  int blk_id = getBlockNumber(val);
  ++blocks[blk_id].count;
  calculateMedian();
}
void remove(int val) {
  if (!nums_count[val])
    return;
  --total_nums_count;
  --nums_count[val];
  int blk_id = getBlockNumber(val);
  --blocks[blk_id].count;
  calculateMedian();
}
void compute() {
  for (int i = 1; i <= n; ++i) {
    ans.found = false;
    switch (queries[i].type) {
      case 'a':
        add(queries[i].val);
        break;
      case 'r':
        remove(queries[i].val);
        break;
    }
    if (!ans.found)
      printf("Wrong!\n");
    else {
      if (ans.b != 0)
        if (ans.a || (!ans.a && ans.sign))
          printf("%d.%d\n", ans.a, ans.b);
        else printf("-%d.%d\n", ans.a, ans.b);
      else printf("%d\n", ans.a);
    }
  }
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf(" %c %d", &queries[i].type, &queries[i].val);
    addToDiffs(queries[i].val, i);
  }
  sort(diffs + 1, diffs + 1 + n, d_comparator);
  compressQs();
  compute();
}
void initBlocks() {
  block_size = BLOCKS_SIZE;
  block_count = BLOCKS_MAX;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
  }
}
int main() {
  freopen("input.txt", "r", stdin);
  initBlocks();
  program();
  return 0;
}
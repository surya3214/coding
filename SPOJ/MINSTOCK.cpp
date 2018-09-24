// AC Trie, Square Root Decomposition
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e6
#define LEN_MAX 10
#define BLOCKS_MAX (int) 1e3
#define ALPHA_CHARS_MAX 26
#define STATES_MAX N_MAX * LEN_MAX
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct {
  int from_query; // if val == 0, invalid
  int go_to[BUFF(ALPHA_CHARS_MAX)];
} trie[BUFF(STATES_MAX)];
int root, total_states;
struct D {
  int val;
  int idx;
} diff_prices[BUFF(N_MAX)];
int d_ptr;
struct {
  int type;
  char x[BUFF(LEN_MAX)];
  int stock_price;
} queries[BUFF(N_MAX)];
int getIndexFromChar(char x) { return x - 'A' + 1; }
int stock_id[BUFF(N_MAX)];
struct {
  int count_in_block;
  int blk_l;
  int blk_r;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(N_MAX, blk_id * block_size); }
void addToDiffPrices(int x, int idx) {
  ++d_ptr;
  diff_prices[d_ptr].val = x;
  diff_prices[d_ptr].idx = idx;
}
bool d_comparator(D a, D b) {
  if (a.val != b.val)
    return a.val < b.val;
  return a.idx < b.idx;
}
void compress() {
  for (int i = 1; i <= d_ptr; ++i)
    queries[diff_prices[i].idx].stock_price = i;
}
void initBlocks() {
  block_size = ceil(sqrt(N_MAX));
  block_count = getBlockNumber(N_MAX);
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
  }
}
int addToTrie(int q_id, bool is_query) {
  int cur_state = root;
  int x;
  for (int i = 0; queries[q_id].x[i]; ++i) {
    x = getIndexFromChar(queries[q_id].x[i]);
    if (!trie[cur_state].go_to[x])
      trie[cur_state].go_to[x] = ++total_states;
    cur_state = trie[cur_state].go_to[x];
  }
  if (is_query)
    return trie[cur_state].from_query;
  trie[cur_state].from_query = q_id;
  return 0;
}
void addStockId(int q_id) {
  stock_id[queries[q_id].stock_price] = q_id;
  int blk_id = getBlockNumber(queries[q_id].stock_price);
  ++blocks[blk_id].count_in_block;
}
void removeStockId(int q_id) {
  stock_id[queries[q_id].stock_price] = 0;
  int blk_id = getBlockNumber(queries[q_id].stock_price);
  --blocks[blk_id].count_in_block;
}
void add(int q_id) {
  addToTrie(q_id, false);
  addStockId(q_id);
}
void update(int q_id) {
  int prev_id = addToTrie(q_id, true);
  removeStockId(prev_id);
  add(q_id);
}
int findLowestAndRemove() {
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    if (blocks[blk_id].count_in_block) {
      for (int i = blocks[blk_id].blk_l; i <= blocks[blk_id].blk_r; ++i) {
        if (stock_id[i]) {
          int ret = stock_id[i];
          removeStockId(stock_id[i]);
          return ret;
        }
      }
    }
  }
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %s", &queries[i].type, queries[i].x);
    if (queries[i].type != 3) {
      scanf("%d", &queries[i].stock_price);
      addToDiffPrices(queries[i].stock_price, i);
    }
  }
  sort(diff_prices + 1, diff_prices + 1 + d_ptr, d_comparator);
  initBlocks();
  compress();
  int x;
  for (int i = 1; i <= n; ++i) {
    switch (queries[i].type) {
      case 1:
        add(i);
        break;
      case 2:
        update(i);
        break;
      case 3:
        x = findLowestAndRemove();
        printf("%s %d\n", queries[x].x, i);
        break;
    }
  }
}
void init() { root = ++total_states; }
int main() {
  init();
  program();
  return 0;
}
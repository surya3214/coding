// WA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define BLOCKS_MAX 337
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
ll waiting;
struct Q {
  int order, required, c_order;
} queries[BUFF(N_MAX)];
struct T {
  int order, id;
} times[BUFF(N_MAX)];
int t_ptr;
int compressed_values[BUFF(N_MAX)];
int c_ptr;
queue<int> qs_processed[BUFF(N_MAX)];
int processed_until, cur_time;
struct B {
  int blk_l, blk_r, blk_cnt;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(N_MAX, blk_id * block_size); }
bool t_comparator(T a, T b) {
  if (a.order != b.order)
    return a.order < b.order;
  return a.id < b.id;
}
bool q_comparator(Q a, Q b) {
  if (a.order != b.order)
    return a.order < b.order;
  return a.required < b.required;
}
void pushToOrderTimes(int order, int id) {
  ++t_ptr;
  times[t_ptr].order = order;
  times[t_ptr].id = id;
}
void compressAndIndex() {
  sort(queries + 1, queries + 1 + n, q_comparator);
  for (int i = 1; i <= n; ++i)
    pushToOrderTimes(queries[i].order, i);
  sort(times + 1, times + 1 + t_ptr, t_comparator);
  int cur_idx, next_idx;
  cur_idx = 1;
  while (cur_idx <= n) {
    compressed_values[++c_ptr] = times[cur_idx].order;
    next_idx = cur_idx + 1;
    while (times[cur_idx].order == times[next_idx].order && next_idx <= n)
      ++next_idx;
    for (int i = cur_idx; i < next_idx; ++i)
      queries[times[cur_idx].id].c_order = c_ptr;
    cur_idx = next_idx;
  }
}
void processUntil(int valid_time) {
  int l_order, blk_id;
  while (processed_until + 1 <= n && queries[processed_until + 1].order <= valid_time) {
    ++processed_until;
    l_order = queries[processed_until].c_order;
    qs_processed[l_order].push(processed_until);
    blk_id = getBlockNumber(l_order);
    ++blocks[blk_id].blk_cnt;
  }
}
int pickCandidate() {
  int ret = 0;
  for (int blk_id = BLOCKS_MAX; blk_id && !ret; --blk_id) {
    if (blocks[blk_id].blk_cnt) {
      for (int x = blocks[blk_id].blk_r; x >= blocks[blk_id].blk_l; --x) {
        if (!qs_processed[x].empty()) {
          ret = qs_processed[x].front();
          break;
        }
      }
    }
  }
  return ret;
}
void process() {
  int candidate, l_order, blk_id;
  cur_time = 0;
  while (processed_until <= n) {
    processUntil(cur_time);
    candidate = pickCandidate();
    if (!candidate) {
      cur_time = queries[processed_until + 1].order;
      processUntil(cur_time);
      candidate = pickCandidate();
    }
    if (!candidate)
      break;
    waiting += queries[candidate].required + cur_time - queries[candidate].order;
    cur_time += queries[candidate].required;
    l_order = queries[candidate].c_order;
    qs_processed[l_order].pop();
    blk_id = getBlockNumber(l_order);
    --blocks[blk_id].blk_cnt;
  }
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &queries[i].order, &queries[i].required);
  compressAndIndex();
  process();
  printf("%lld\n", waiting / n);
}
void readyUp() {
  block_size = block_count = BLOCKS_MAX;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
  }
}
int main() {
  freopen("input.txt", "r", stdin);
  readyUp();
  program();
  return 0;
}
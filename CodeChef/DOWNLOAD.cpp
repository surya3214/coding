// TLE
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define K_MAX 20
#define Q_MAX 5000
#define VAL_MAX 100000
#define BLOCKS_MAX 317
#define BLOCK_SIZE 317
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct I {
  int s, e;
} intervals[BUFF(N_MAX)];
int n;
struct Q {
  int k;
  int aliens[BUFF(K_MAX)];
  vector<int> c_aliens;
} queries[BUFF(Q_MAX)];
int q;
struct S {
  int val;
  bitset<BUFF(N_MAX)> points;
} s_values[BUFF(N_MAX)];
int s_ptr;
struct B {
  int blk_l, blk_r;
  int min, max;
  bitset<BUFF(N_MAX)> dirty;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(s_ptr, (blk_id * block_size)); }
struct V {
  int val, id;
} values[BUFF(VAL_MAX)];
int v_ptr;
void addToValues(int val, int id) {
  ++v_ptr;
  values[v_ptr].val = val;
  values[v_ptr].id = id;
}
bool v_comparator(V a, V b) { return a.val < b.val; }
void addToSValues(int val) {
  ++s_ptr;
  s_values[s_ptr].val = val;
}
void compressAndIndex() {
  sort(values + 1, values + 1 + v_ptr, v_comparator);
  int c_id, last_val;
  c_id = 0, last_val = -1;
  for (int i = 1; i <= v_ptr; ++i) {
    if (values[i].val != last_val) {
      ++c_id;
      last_val = values[i].val;
      addToSValues(values[i].val);
    }
    queries[values[i].id].c_aliens.push_back(c_id);
  }
}
void buildBlocks() {
  block_size = BLOCK_SIZE;
  block_count = getBlockNumber(s_ptr);
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
    blocks[blk_id].min = s_values[blocks[blk_id].blk_l].val;
    blocks[blk_id].max = s_values[blocks[blk_id].blk_r].val;
  }
}
void addIntervals(int id, int s, int e) {
  int l, r;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    if (blocks[blk_id].min > e)
      break;
    if (blocks[blk_id].min >= s && blocks[blk_id].max <= e) {
      blocks[blk_id].dirty[id] = 1;
    } else {
      for (int x = blocks[blk_id].blk_l; x <= blocks[blk_id].blk_r; ++x) {
        if (s_values[x].val >= s && s_values[x].val <= e)
          s_values[x].points[id] = 1;
      }
    }
  }
}
void process() {
  for (int i = 1; i <= n; ++i)
    addIntervals(i, intervals[i].s, intervals[i].e);
}
bitset<BUFF(N_MAX)> answer;
int getAnswer(int id) {
  answer.reset();
  int blk_id, c_val;
  for (int i = 1; i <= queries[id].k; ++i) {
    c_val = queries[id].c_aliens[i - 1];
    blk_id = getBlockNumber(c_val);
    answer = (answer | blocks[blk_id].dirty | s_values[c_val].points);
  }
  return answer.count();
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &intervals[i].s, &intervals[i].e);
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &queries[i].k);
    for (int j = 1; j <= queries[i].k; ++j) {
      scanf("%d", &queries[i].aliens[j]);
      addToValues(queries[i].aliens[j], i);
    }
  }
  compressAndIndex();
  buildBlocks();
  process();
  for (int i = 1; i <= q; ++i)
    printf("%d\n", getAnswer(i));
}
int main() {
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}
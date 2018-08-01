// AC Ayyyyyyyyyyyyyyyyy! SQRT Decomposition, Heap
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define BLOCKS_MAX 317
#define BLOCKS_SIZE 317
using namespace std;
typedef long long int ll;
int n, k;
ll t_array[BUFF(N_MAX)];
ll min_t_array[BUFF(N_MAX)];
struct {
  int idx;
  ll val;
} min_heap[BUFF(N_MAX)], t_heap;
int heap_ptr;
int valid_entry;
struct {
  ll min;
  ll max;
  int time;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, b_time;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
int getLeftHeapChild(int x) { return 2 * x; }
int getRightHeapChild(int x) { return (2 * x) + 1; }
int getParentHeap(int x) { return x / 2; }
int getSquareRootOf(int x) {
  int i = 2;
  while (i * i <= x) ++i;
  return i - 1;
}
void reset() {
  ++b_time;
  heap_ptr = 0, valid_entry = -(k - 1);
  // block_size = getSquareRootOf(n);
}
void swapHeap(int x, int y) {
  t_heap = min_heap[x];
  min_heap[x] = min_heap[y];
  min_heap[y] = t_heap;
}
void heapifyUp() {
  int x = heap_ptr;
  int parent = getParentHeap(x);
  while (x > 1 && min_heap[x].val < min_heap[parent].val) {
    swapHeap(x, parent);
    x = parent;
    parent = getParentHeap(x);
  }
}
void pushToHeap(ll val, int i) {
  ++heap_ptr;
  min_heap[heap_ptr].val = val;
  min_heap[heap_ptr].idx = i;
  heapifyUp();
}
void heapifyDown() {
  int x = 1;
  int left, right, move_to;
  while (x <= heap_ptr) {
    left = getLeftHeapChild(x);
    right = getRightHeapChild(x);
    move_to = 0;
    if (left <= heap_ptr && min_heap[left].val < min_heap[x].val)
      move_to = 1;
    if (right <= heap_ptr && min_heap[right].val < min_heap[x].val && min_heap[right].val < min_heap[left].val)
      move_to = 2;
    if (move_to == 0) break;
    else if (move_to == 1) {
      swapHeap(x, left);
      x = left;
    } else if (move_to == 2) {
      swapHeap(x, right);
      x = right;
    }
  }
}
void removeHeapHead() {
  while (min_heap[heap_ptr].idx < valid_entry)
    --heap_ptr;
  min_heap[1] = min_heap[heap_ptr];
  --heap_ptr;
  heapifyDown();
}
void setMin(int blk_id, ll val) {
  if (blocks[blk_id].time != b_time) {
    blocks[blk_id].max = blocks[blk_id].min = val;
    blocks[blk_id].time = b_time;
  } else {
    blocks[blk_id].min = min(blocks[blk_id].min, val);
    blocks[blk_id].max = max(blocks[blk_id].max, val);
  }
}
struct {
  bool set;
  ll max;
} ans;
void compareWithAns(ll val) {
  if (!ans.set) {
    ans.max = val;
    ans.set = true;
  } else ans.max = max(ans.max, val);
}
void findMax(int l, int r) {
  ans.set = false;
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    if (l == blk_l && blk_r <= r) {
      compareWithAns(blocks[blk_id].max);
      l = blk_r + 1;
    } else {
      int t_r = min(blk_r, r);
      for (int i = l; i <= t_r; ++i)
        compareWithAns(min_t_array[i]);
      l = t_r + 1;
    }
  }
}
void program() {
  int tcase;
  int q, l, r;
  scanf("%d", &tcase);
  block_size = BLOCKS_SIZE;
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &k);
    reset();
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", &t_array[i]);
      ++valid_entry;
      pushToHeap(t_array[i], i);
      if (valid_entry >= 1 && valid_entry <= n - k + 1) {
        while (min_heap[1].idx < valid_entry)
          removeHeapHead();
        min_t_array[valid_entry] = min_heap[1].val;
        setMin(getBlockNumber(valid_entry), min_heap[1].val);
      }
    }
    scanf("%d", &q);
    printf("Case %d:\n", t);
    for (int i = 1; i <= q; ++i) {
      scanf("%d %d", &l, &r);
      r = r - k + 1;
      if (l <= r) {
        findMax(l, r);
        printf("%lld\n", ans.max);
      } else printf("Impossible\n");
    }
  }
}
int main() {
  program();
  return 0;
}
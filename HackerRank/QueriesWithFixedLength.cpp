// AC Window Heap
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (1e5)
#define HEAP_HEAD 1
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, d, ans, valid_from;
int nums[BUFF(N_MAX)];
struct H {
  int idx;
  int val;
} max_heap[BUFF(N_MAX)];
int heap_ptr;
int getHeapParent(int x) { return x / 2; }
int getHeapLeft(int x) { return 2 * x; }
int getHeapRight(int x) { return 2 * x + 1; }
void reset() { heap_ptr = 0; }
void h_swap(int i, int j) {
  struct H t = max_heap[i];
  max_heap[i] = max_heap[j];
  max_heap[j] = t;
}
void heapifyUp() {
  int x = heap_ptr;
  int parent;
  while (x != HEAP_HEAD) {
    parent = getHeapParent(x);
    if (max_heap[x].val > max_heap[parent].val) {
      h_swap(x, parent);
      x = parent;
    } else break;
  }
}
void heapifyDown() {
  int x = HEAP_HEAD, l, r;
  while (x <= heap_ptr) {
    l = getHeapLeft(x);
    r = getHeapRight(x);
    if (r <= heap_ptr) {
      if (max_heap[r].val >= max_heap[l].val && max_heap[r].val > max_heap[x].val) {
        h_swap(r, x);
        x = r;
      } else if (max_heap[l].val >= max_heap[r].val && max_heap[l].val > max_heap[x].val) {
        h_swap(l, x);
        x = l;
      } else break;
    } else if (l <= heap_ptr) {
      if (max_heap[l].val > max_heap[x].val) {
        h_swap(l, x);
        x = l;
      } else break;
    } else break;
  }
}
void removeHeapHead() {
  while (heap_ptr != HEAP_HEAD && max_heap[heap_ptr].idx < valid_from)
    --heap_ptr;
  h_swap(heap_ptr, HEAP_HEAD);
  --heap_ptr;
  heapifyDown();
}
void pushToHeap(int idx, int val) {
  ++heap_ptr;
  max_heap[heap_ptr].idx = idx;
  max_heap[heap_ptr].val = val;
  heapifyUp();
}
void heapWindow() {
  reset();
  for (int i = 1; i <= d; ++i)
    pushToHeap(i, nums[i]);
  valid_from = 1;
  ans = max_heap[HEAP_HEAD].val;
  while (d != n) {
    ++d;
    ++valid_from;
    pushToHeap(d, nums[d]);
    while (max_heap[HEAP_HEAD].idx < valid_from)
      removeHeapHead();
    ans = min(ans, max_heap[HEAP_HEAD].val);
  }
}
void program() {
  int q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &nums[i]);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &d);
    heapWindow();
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
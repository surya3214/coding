// AC Max Heap, Sliding Window
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define HEAP_HEAD 1
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, k, valid;
int inp[BUFF(N_MAX)];
struct H {
  int val;
  int idx;
} max_heap[BUFF(N_MAX)], t;
int heap_ptr;
int getHeapParent(int x) { return x / 2; }
int getHeapLeftChild(int x) { return x * 2; }
int getHeapRightChild(int x) { return x * 2 + 1; }
void swapHeapNodes(int a, int b) {
  t = max_heap[a];
  max_heap[a] = max_heap[b];
  max_heap[b] = t;
}
void heapifyUp() {
  int x = heap_ptr;
  int parent;
  while (x != HEAP_HEAD) {
    parent = getHeapParent(x);
    if (max_heap[parent].val < max_heap[x].val) {
      swapHeapNodes(parent, x);
      x = parent;
    } else break;
  }
}
void heapifyDown() {
  int x = HEAP_HEAD;
  int left, right, move_to;
  while (x <= heap_ptr) {
    left = getHeapLeftChild(x);
    right = getHeapRightChild(x);
    move_to = 0;
    if (left <= heap_ptr && max_heap[left].val > max_heap[x].val)
      move_to = 1;
    if (right <= heap_ptr && max_heap[right].val > max_heap[x].val && max_heap[right].val > max_heap[left].val)
      move_to = 2;
    if (!move_to)
      break;
    else if (move_to == 1) {
      swapHeapNodes(x, left);
      x = left;
    } else if (move_to == 2) {
      swapHeapNodes(x, right);
      x = right;
    }
  }
}
void removeHeapHead() {
  while (max_heap[heap_ptr].idx < valid)
    --heap_ptr;
  swapHeapNodes(HEAP_HEAD, heap_ptr);
  heapifyDown();
}
void pushToHeap(int x, int idx) {
  ++heap_ptr;
  max_heap[heap_ptr].val = x;
  max_heap[heap_ptr].idx = idx;
  heapifyUp();
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &inp[i]);
  scanf("%d", &k);
  for (int i = 1; i < k; ++i)
    pushToHeap(inp[i], i);
  valid = 1;
  for (int i = k; i <= n; ++i) {
    pushToHeap(inp[i], i);
    while (max_heap[HEAP_HEAD].idx < valid)
      removeHeapHead();
    printf("%d ", max_heap[HEAP_HEAD]);
    ++valid;
  }
}
int main() {
  program();
  return 0;
}
// AC Heap
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e6
#define HEAP_HEAD 1
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int heap[BUFF(N_MAX)];
int h_ptr;
int getHeapParent(int x) { return x / 2; }
int getHeapLeftChild(int x) { return 2 * x; }
int getHeapRightChild(int x) { return 2 * x + 1; }
void heapifyUp() {
  int cur = h_ptr, parent;
  parent = getHeapParent(cur);
  while (parent) {
    if (heap[cur] < heap[parent])
      swap(heap[cur], heap[parent]);
    else break;
    cur = parent;
    parent = getHeapParent(cur);
  }
}
void pushToHeap(int x) {
  ++h_ptr;
  heap[h_ptr] = x;
  heapifyUp();
}
void heapifyDown() {
  int cur = HEAP_HEAD, left, right, move_to;
  while (1) {
    left = getHeapLeftChild(cur);
    right = getHeapRightChild(cur);
    move_to = 0;
    if (right <= h_ptr) {
      if (heap[right] < heap[cur] && heap[right] <= heap[left])
        move_to = 2;
      else if (heap[left] < heap[cur] && heap[left] <= heap[right])
        move_to = 1;
    } else if (left <= h_ptr) {
      if (heap[left] < heap[cur])
        move_to = 1;
    }
    if (move_to == 1) {
      swap(heap[cur], heap[left]);
      cur = left;
    } else if (move_to == 2) {
      swap(heap[cur], heap[right]);
      cur = right;
    } else break;
  }
}
void removeHeapHead() {
  swap(heap[HEAP_HEAD], heap[h_ptr]);
  --h_ptr;
  heapifyDown();
}
void program() {
  int n, k, x, moves = 0;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    pushToHeap(x);
  }
  while (h_ptr != HEAP_HEAD && heap[HEAP_HEAD] < k) {
    x = heap[HEAP_HEAD];
    removeHeapHead();
    x = x + (2 * heap[HEAP_HEAD]);
    removeHeapHead();
    pushToHeap(x);
    ++moves;
  }
  if (heap[HEAP_HEAD] < k)
    moves = -1;
  printf("%d\n", moves);
}
int main() {
  program();
  return 0;
}
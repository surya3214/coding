// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define Q_MAX (int) 1e5
#define HEAP_HEAD 1
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct H {
  int val;
} heap1[BUFF(Q_MAX)], heap2[BUFF(Q_MAX)];
int h1_ptr, h2_ptr;
int getHeapParent(int x) { return x / 2; }
int getHeapLeftChild(int x) { return 2 * x; }
int getHeapRightChild(int x) { return 2 * x + 1; }
void h_swap(int l, int r, bool type) {
  struct H *p, t;
  if (type)
    p = heap2;
  else p = heap1;
  t = p[l];
  p[l] = p[r];
  p[r] = t;
}
void heapifyDown(bool type) {
  struct H *p;
  int size;
  if (type)
    p = heap2, size = h2_ptr;
  else p = heap1, size = h1_ptr;
  int cur, left, right, move_to;
  cur = HEAP_HEAD;
  while (1) {
    move_to = 0;
    left = getHeapLeftChild(cur);
    right = getHeapRightChild(cur);
    if (right <= size) {
      if (p[right].val < p[cur].val && p[right].val <= p[left].val)
        move_to = 2;
      else if (p[left].val < p[cur].val && p[left].val <= p[right].val)
        move_to = 1;
    } else if (left <= size) {
      if (p[left].val < p[cur].val)
        move_to = 1;
    }
    if (move_to == 1) {
      h_swap(cur, left, type);
      cur = left;
    } else if (move_to == 2) {
      h_swap(cur, right, type);
      cur = right;
    } else break;
  }
}
void removeHeapHead(bool type) {
  if (type) {
    heap2[HEAP_HEAD] = heap2[h2_ptr];
    --h2_ptr;
  } else {
    heap1[HEAP_HEAD] = heap1[h1_ptr];
    --h1_ptr;
  }
  heapifyDown(type);
}
void heapifyUp(bool type) {
  struct H *p;
  int cur, parent;
  if (type)
    p = heap2, cur = h2_ptr;
  else p = heap1, cur = h1_ptr;
  parent = getHeapParent(cur);
  while (parent) {
    if (p[cur].val < p[parent].val) {
      h_swap(cur, parent, type);
      cur = parent;
    } else break;
    parent = getHeapParent(cur);
  }
}
void pushToHeap(int v, bool type) {
  if (type) {
    ++h2_ptr;
    heap2[h2_ptr].val = v;
  } else {
    ++h1_ptr;
    heap1[h1_ptr].val = v;
  }
  heapifyUp(type);
}
void program() {
  int q, type, v;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &type);
    if (type == 3) {
      while (h2_ptr && (heap1[HEAP_HEAD].val == heap2[HEAP_HEAD].val)) {
        removeHeapHead(false);
        removeHeapHead(true);
      }
      printf("%d\n", heap1[HEAP_HEAD].val);
    } else {
      scanf("%d", &v);
      if (type == 1)
        pushToHeap(v, false);
      else pushToHeap(v, true);
    }
  }
}
int main() {
  program();
  return 0;
}
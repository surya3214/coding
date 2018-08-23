// TLE
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 2500
#define M_MAX 2500
#define HEAP_HEAD 1
#define INF 1e9
#pragma GCC optimize "O4"
#define D_MAX N_MAX * M_MAX
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m, k;
struct {
  int l, r;
  ll beauty[BUFF(M_MAX)];
} flowers[BUFF(N_MAX)];
ll d_beauty[BUFF(D_MAX)];
int t_cnt[BUFF(D_MAX)];
struct H {
  ll val;
  int idx;
} min_heap[BUFF(N_MAX)];
int heap_ptr;
int getHeapParent(int x) { return x / 2; }
int getHeapLeftChild(int x) { return 2 * x; }
int getHeapRightChild(int x) { return 2 * x + 1; }
void addToFlowersBeauty(int i, int j, ll x) {
  int pos = ++d_beauty[0];
  d_beauty[pos] = flowers[i].beauty[j] = x;
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int findBS(ll x) {
  int l, r;
  l = 1, r = d_beauty[0];
  int mid;
  while (l <= r) {
    mid = getMid(l, r);
    if (d_beauty[mid] == x)
      return mid;
    else if (d_beauty[mid] < x)
      l = mid + 1;
    else r = mid - 1;
  }
}
void removeBeautyDuplicates() {
  int last = 1;
  for (int j = 2; j <= d_beauty[0]; ++j)
    if (d_beauty[j] != d_beauty[last])
      d_beauty[++last] = d_beauty[j];
  d_beauty[0] = last;
}
void swapHeap(int i, int j) {
  struct H tmp;
  tmp = min_heap[i];
  min_heap[i] = min_heap[j];
  min_heap[j] = tmp;
}
void heapifyUp() {
  int t = heap_ptr;
  int parent;
  while (t != HEAP_HEAD) {
    parent = getHeapParent(t);
    if (min_heap[t].val < min_heap[parent].val) {
      swapHeap(parent, t);
      t = parent;
    } else break;
  }
}
struct {
  bool set;
  ll best;
  int min_idx, max_idx;
} ans;
void updateBest() {
  assert(ans.min_idx != INF);
  assert(ans.max_idx != 0);
  ll x = d_beauty[ans.max_idx] - d_beauty[ans.min_idx];
  if (ans.set) ans.best = min(ans.best, x);
  else {
    ans.best = x;
    ans.set = true;
  }
}
void addToHeap(ll val, int idx) {
  ++heap_ptr;
  min_heap[heap_ptr].val = val;
  min_heap[heap_ptr].idx = idx;
  heapifyUp();
}
void addFlowersCount(int i) {
  int x;
  // x = findBS(flowers[i].beauty[flowers[i].l]);
  x = flowers[i].beauty[flowers[i].l]; x %= D_MAX;
  ++t_cnt[x];
  if (x < ans.min_idx)
    ans.min_idx = x;
  // x = findBS(flowers[i].beauty[flowers[i].r]);
  x = flowers[i].beauty[flowers[i].r]; x %= D_MAX;
  ++t_cnt[x];
  if (x > ans.max_idx) ans.max_idx = x;
  if (flowers[i].r + 1 <= m)
    addToHeap(flowers[i].beauty[flowers[i].r + 1], i);
}
void removeFlowersCount(int i) {
  int x;
  // x = findBS(flowers[i].beauty[flowers[i].l]);
  x = flowers[i].beauty[flowers[i].l]; x %= D_MAX;
  --t_cnt[x];
  if (ans.min_idx == x && t_cnt[x] == 0) {
    ans.min_idx = INF;
    for (int j = x + 1; j <= d_beauty[0]; ++j) {
      if (t_cnt[j]) {
        ans.min_idx = j;
        break;
      }
    }
  }
  // x = findBS(flowers[i].beauty[flowers[i].r]);
  x = flowers[i].beauty[flowers[i].r]; x %= D_MAX;
  --t_cnt[x];
}
void heapifyDown() {
  int x = 1;
  int left, right, move_to;
  while (x <= heap_ptr) {
    left = getHeapLeftChild(x);
    right = getHeapRightChild(x);
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
  min_heap[HEAP_HEAD] = min_heap[heap_ptr];
  --heap_ptr;
  heapifyDown();
}
void compute() {
  int idx;
  ans.min_idx = INF;
  ans.max_idx = 0;
  for (int i = 1; i <= n; ++i) {
    flowers[i].l = 1;
    flowers[i].r = k;
    addFlowersCount(i);
  }
  updateBest();
  while (heap_ptr >= HEAP_HEAD) {
    idx = min_heap[HEAP_HEAD].idx;
    removeHeapHead();
    if (flowers[idx].r < m) {
      removeFlowersCount(idx);
      ++flowers[idx].l;
      ++flowers[idx].r;
      addFlowersCount(idx);
    }
    updateBest();
  }
}
void program() {
  ll a, b, c, x;
  int l, r;
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld %lld %lld %lld", &x, &a, &b, &c);
    for (int j = 1; j <= m; ++j) {
      addToFlowersBeauty(i, j, x);
      x = (a * x + b) % c;
    }
    sort(flowers[i].beauty + 1, flowers[i].beauty + 1 + m);
  }
  sort(d_beauty + 1, d_beauty + 1 + d_beauty[0]);
  removeBeautyDuplicates();
  compute();
  printf("%lld\n", ans.best);
}
int main() {
  program();
  return 0;
}
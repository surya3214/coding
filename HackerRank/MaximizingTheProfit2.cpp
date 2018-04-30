// AC Square Root Decomposition, Doubly Linked List
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 3 * 100000
#define VAL_MAX 1000000
#define BLOCKS_MAX 1000
#define BLOCK_SIZE 1000
#define SIGNS 2
#define POSITIVE 1
#define NEGATIVE 0
#define INVALID -(VAL_MAX + 1)
using namespace std;
typedef long long int ll;
struct L {
  int val;
  struct L *left;
  struct L *right;
} nodes[BUFF(N_MAX)], *rear;
struct P {
  int val;
  struct L *ptr;
} profits[BUFF(N_MAX)];
ll ans;
int sorted_indices[BUFF(N_MAX)], buff1[BUFF(N_MAX / 2)], buff2[BUFF(N_MAX / 2)];
int n, a1, a2, b, c1, c2;
struct {
  int elements[BUFF(BLOCK_SIZE)];
} blocks[BUFF(SIGNS)][BUFF(BLOCKS_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
int getBlockNumber(int val) { val = (val >= 0) ? val: -val; if(val == 0) return 1; return (val - 1) / BLOCK_SIZE + 1; }
void merge(int s1, int e1, int e2) {
  int s2 = e1 + 1;
  int b1, b2, t1, t2;
  b1 = b2 = 0;
  for (int i = s1; i <= e1; i++)
    buff1[b1++] = sorted_indices[i];
  for (int i = s2; i <= e2; i++)
    buff2[b2++] = sorted_indices[i];
  int ptr;
  ptr = s1;
  t1 = t2 = 0;
  int *p = sorted_indices;
  int a, b;
  while (t1 < b1 && t2 < b2) {
    a = profits[buff1[t1]].val;
    b = profits[buff2[t2]].val;
    if (a < b || (a == b && buff1[t1] > buff2[t2]))
      p[ptr++] = buff1[t1++];
    else p[ptr++] = buff2[t2++];
  }
  while (t1 < b1) p[ptr++] = buff1[t1++];
  while (t2 < b2) p[ptr++] = buff2[t2++];
}
void merge_sort(int l, int r) {
  if (l < r) {
    int mid = getMid(l, r);
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);
  }
}
void reset() {
  ans = INVALID;
  n = 0;
  for (int i = 0; i <= BLOCKS_MAX; i++) {
    blocks[POSITIVE][i].elements[0] = 0;
    blocks[NEGATIVE][i].elements[0] = 0;
  }
}
void resetVars() { a1 = a2 = c1 = c2 = INVALID;}
void removeFromList(struct L *t) {
  if (t == rear) {
    rear = rear->left;
    rear->right = nullptr;
    return;
  }
  struct L *prev = t->left;
  if (prev) prev->right = t->right;
  if (t->right) {
    t->right->left = t->left;
    c1 = t->right->val;
  }
  c2 = rear->val;
}
void pushToBlock(int val) {
  bool sign;
  if (val > 0) sign = POSITIVE;
  else sign = NEGATIVE;
  int blk = getBlockNumber(val);
  int pos = ++blocks[sign][blk].elements[0];
  blocks[sign][blk].elements[pos] = val;
}
int my_min(int a, int b) {
  if (a == INVALID) return b;
  else return a < b ? a : b;
}
void findLowestA1InBlock(int blk, bool sign) {
  for (int j = 1; j <= blocks[sign][blk].elements[0]; j++) {
    if (blocks[sign][blk].elements[j] < b)
      a1 = my_min(a1, blocks[sign][blk].elements[j]);
  }
}
int my_max(int a, int b) {
  if (a == INVALID) return b;
  else return a > b ? a : b;
}
void findLowestA1InNegative(int blk) {
  bool sign = NEGATIVE;
  for (int i = BLOCK_SIZE; i > blk && a1 == INVALID; i--) {
    if (blocks[sign][i].elements[0]) {
      for (int j = 1; j <= blocks[sign][i].elements[0]; j++) {
        if (blocks[sign][i].elements[j] < b)
          a1 = my_min(a1, blocks[sign][i].elements[j]);
      }
    }
  }
}
void findLowestA1InPositive(int blk) {
  bool sign = POSITIVE;
  for (int i = 1; i < blk && a1 == INVALID; i++) {
    if (blocks[sign][i].elements[0]) {
      for (int j = 1; j <= blocks[sign][i].elements[0]; j++) {
        if (blocks[sign][i].elements[j] < b)
          a1 = my_min(a1, blocks[sign][i].elements[j]);
      }
    }
  }
}
void identifyA1() {
  int blk;
  if (b <= 0) {
    blk = getBlockNumber(b);
    findLowestA1InNegative(blk);
    if (a1 == INVALID) findLowestA1InBlock(blk, NEGATIVE);
  } else {
    blk = getBlockNumber(b);
    findLowestA1InNegative(0);
    if (a1 == INVALID) findLowestA1InPositive(blk);
    if (a1 == INVALID) findLowestA1InBlock(blk, POSITIVE);
  }
}
void findHighestA2InBlock(int blk, bool sign) {
  for (int j = 1; j <= blocks[sign][blk].elements[0]; j++) {
    if (blocks[sign][blk].elements[j] < b)
      a2 = my_max(a2, blocks[sign][blk].elements[j]);
  }
}
void findHighestA2InNegative(int blk) {
  bool sign = NEGATIVE;
  for (int i = blk; i <= BLOCK_SIZE && a2 == INVALID; i++) {
    if (blocks[sign][i].elements[0]) {
      for (int j = 1; j <= blocks[sign][i].elements[0]; j++) {
        if (blocks[sign][i].elements[j] < b)
          a2 = my_max(a2, blocks[sign][i].elements[j]);
      }
    }
  }
}
void findHighestA2InPositive(int blk) {
  bool sign = POSITIVE;
  for (int i = 1; i <= blk && a2 == INVALID; i++) {
    if (blocks[sign][i].elements[0]) {
      for (int j = 1; j <= blocks[sign][i].elements[0]; j++) {
        if (blocks[sign][i].elements[j] < b)
          a2 = my_max(a2, blocks[sign][i].elements[j]);
      }
    }
  }
}
void identifyA2() {
  int blk;
  if (b <= 0) {
    blk = getBlockNumber(b);
    findHighestA2InBlock(blk, NEGATIVE);
    if (a2 == INVALID) findHighestA2InNegative(blk + 1);
  } else {
    blk = getBlockNumber(b);
    findHighestA2InBlock(blk, POSITIVE);
    if (a2 == INVALID) findHighestA2InPositive(blk - 1);
    if (a2 == INVALID) findHighestA2InNegative(1);
  }
}
void identifyASet() {
  identifyA1();
  if (a1 != INVALID)
    identifyA2();
}
ll my_max(ll a, ll b) {
  if (a == INVALID) return b;
  else return a > b ? a : b;
}
void computeAns() {
  if ((a1 == INVALID && a2 == INVALID))
    return;
  if (a1 != INVALID) {
    if (c1 != INVALID) ans = my_max(ans, (ll) a1 * b * c1);
    if (c2 != INVALID) ans = my_max(ans, (ll) a1 * b * c2);
  }
  if (a2 != INVALID) {
    if (c1 != INVALID) ans = my_max(ans, (ll) a2 * b * c1);
    if (c2 != INVALID) ans = my_max(ans, (ll) a2 * b * c2);
  }
}
void solve() {
  merge_sort(1, n);
  struct P *p;
  for (int i = 1; i <= n; i++) {
    if (i == 1) nodes[i].left = nullptr;
    else nodes[i].left = &nodes[i - 1];
    if (i == n) nodes[i].right = nullptr;
    else nodes[i].right = &nodes[i + 1];
    p = &profits[sorted_indices[i]];
    nodes[i].val = p->val;
    p->ptr = &nodes[i];
  }
  rear = &nodes[n];
  removeFromList(profits[1].ptr);
  pushToBlock(profits[1].val);
  for (int i = 2; i < n; i++) {
    resetVars();
    removeFromList(profits[i].ptr);
    b = profits[i].val;
    if (!(c1 == INVALID && c2 == INVALID))
      identifyASet();
    computeAns();
    pushToBlock(profits[i].val);
  }
}
long maximumProfit(vector<int> p) {
  reset();
  for (vector<int>::iterator it = p.begin(); it != p.end(); it++) {
    ++n;
    sorted_indices[n] = n;
    profits[n].val = *it;
  }
  solve();
  return ans == INVALID ? -1 : ans;
}
void program() {
  reset();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &profits[i].val);
    sorted_indices[i] = i;
  }
  solve();
  printf("%lld\n", ans == INVALID ? -1 : ans);
}
int main() {
  freopen("HackerRank/MaximizingTheProfit_input.txt", "r", stdin);
  program();
  return 0;
}
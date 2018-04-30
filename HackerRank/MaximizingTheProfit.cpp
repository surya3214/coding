//
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 3 * 100000
#define P_MAX 1000000
#define BLOCKS_MAX 550
#define INVALID P_MAX + 1
#define SIGNS 2
#define POSITIVE 0
#define NEGATIVE 1
#define POSITIONS 2
#define ONE 1
#define TWO 2
using namespace std;
int indices[BUFF(N_MAX)], buff1[BUFF(N_MAX / 2)], buff2[BUFF(N_MAX / 2)];
int block_size;
struct {
  long val;
} profits[BUFF(N_MAX)];
int n;
long min_values[BUFF(SIGNS)];
long ans;
struct B {
  long bundle[BUFF(SIGNS)][BUFF(POSITIONS)];
} blocks[BUFF(BLOCKS_MAX)], blank;
int getMid(int l, int r) { return l + (r - l) / 2; }
int getBlockNumber(int idx) { return (idx - 1) / block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
int getBlockLeft(int blk_id) { return getBlockRight(blk_id - 1) + 1; }
void resetBlank() {
  blank.bundle[POSITIVE][ONE] = blank.bundle[POSITIVE][TWO] = INVALID;
  blank.bundle[NEGATIVE][ONE] = blank.bundle[NEGATIVE][TWO] = INVALID;
}
bool validate(long &a) { return !(a == INVALID); }
long my_max(long a, long b) {
  if (!validate(a) && !validate(b))
    return INVALID;
  else if (!validate(b))
    return a;
  else if (!validate(a))
    return b;
  else return max(a, b);
}
void reset() { 
  ans = INVALID, n = 0;
  min_values[POSITIVE] = min_values[NEGATIVE] = INVALID;
  resetBlank();
  for (int i = 0; i <= BLOCKS_MAX; i++)
    blocks[i] = blank;
}
void merge(int s1, int e1, int e2) {
  int s2 = e1 + 1;
  int *p = indices;
  int b1, b2;
  int t1, t2;
  b1 = b2 = 0;
  t1 = s1, t2 = s2;
  while (t1 <= e1)
    buff1[b1++] = p[t1++];
  while (t2 <= e2)
    buff2[b2++] = p[t2++];
  t1 = 0, t2 = 0;
  int ptr = s1;
  while (t1 < b1 && t2 < b2) {
    if (profits[buff1[t1]].val <= profits[buff2[t2]].val)
      p[ptr++] = buff1[t1++];
    else p[ptr++] = buff2[t2++];
  }
  while (t1 < b1)
    p[ptr++] = buff1[t1++];
  while (t2 < b2)
    p[ptr++] = buff2[t2++];
}
void merge_sort(int l, int r) {
  if (l < r) {
    int mid = getMid(l, r);
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);
  }
}
void fillBlank(int idx, long val) {
  int l = 1;
  int blk, blk_r;
  struct B *p, *q;
  p = &blank;
  while (l <= idx) {
    blk = getBlockNumber(l);
    blk_r = getBlockRight(blk);
    if (blk_r <= idx) {
      q = &blocks[blk];
      
      if (validate(p->bundle[POSITIVE][ONE]) && validate(q->bundle[POSITIVE][ONE]))
        p->bundle[POSITIVE][TWO] = my_max(p->bundle[POSITIVE][TWO], p->bundle[POSITIVE][ONE] * q->bundle[POSITIVE][ONE]);
      if (validate(p->bundle[NEGATIVE][ONE]) && validate(q->bundle[NEGATIVE][ONE]))
        p->bundle[POSITIVE][TWO] = my_max(p->bundle[POSITIVE][TWO], p->bundle[NEGATIVE][ONE] * q->bundle[NEGATIVE][ONE]);
      p->bundle[POSITIVE][TWO] = my_max(p->bundle[POSITIVE][TWO], q->bundle[POSITIVE][TWO]);

      if (validate(p->bundle[NEGATIVE][ONE]) && validate(q->bundle[POSITIVE][ONE]))
        p->bundle[NEGATIVE][TWO] = my_max(p->bundle[NEGATIVE][TWO], p->bundle[NEGATIVE][ONE] * q->bundle[POSITIVE][ONE]);
      if (validate(p->bundle[POSITIVE][ONE]) && validate(q->bundle[NEGATIVE][ONE]))
        p->bundle[NEGATIVE][TWO] = my_max(p->bundle[NEGATIVE][TWO], p->bundle[POSITIVE][ONE] * q->bundle[NEGATIVE][ONE]);
      p->bundle[NEGATIVE][TWO] = my_max(p->bundle[NEGATIVE][TWO], q->bundle[NEGATIVE][TWO]);

      p->bundle[POSITIVE][ONE] = my_max(p->bundle[POSITIVE][ONE], q->bundle[POSITIVE][ONE]);
      p->bundle[NEGATIVE][ONE] = my_max(p->bundle[NEGATIVE][ONE], q->bundle[NEGATIVE][ONE]);
      l = blk_r + 1;
    } else {
      int cur_val;
      for (int i = l; i <= idx; i++) {
        cur_val = profits[indices[i]].val;
        if (cur_val < val) { // i < j < k
          if (cur_val >= 0) { // cur_val is +ve
            if (validate(p->bundle[POSITIVE][ONE]))
              p->bundle[POSITIVE][TWO] = my_max(p->bundle[POSITIVE][TWO], cur_val * p->bundle[POSITIVE][ONE]);
            if (validate(p->bundle[NEGATIVE][ONE]))
              p->bundle[NEGATIVE][TWO] = my_max(p->bundle[NEGATIVE][TWO], cur_val * p->bundle[NEGATIVE][ONE]);
            p->bundle[POSITIVE][ONE] = my_max(p->bundle[POSITIVE][ONE], cur_val);
          } else { // cur_val is -ve
            if (validate(p->bundle[POSITIVE][ONE]))
              p->bundle[NEGATIVE][TWO] = my_max(p->bundle[NEGATIVE][TWO], cur_val * p->bundle[POSITIVE][ONE]);
            if (validate(p->bundle[NEGATIVE][ONE]))
              p->bundle[POSITIVE][TWO] = my_max(p->bundle[POSITIVE][TWO], cur_val * p->bundle[NEGATIVE][ONE]);
            p->bundle[NEGATIVE][ONE] = my_max(p->bundle[NEGATIVE][ONE], cur_val);
          }
        }
      }
      l = idx + 1;
    }
  }
}
void addToBlock(int idx, int cur_val) {
  int blk = getBlockNumber(idx);
  struct B *p = &blocks[blk];
  if (cur_val >= 0) { // cur_val is +ve
    if (validate(p->bundle[POSITIVE][ONE]))
      p->bundle[POSITIVE][TWO] = my_max(p->bundle[POSITIVE][TWO], cur_val * p->bundle[POSITIVE][ONE]);
    if (validate(p->bundle[NEGATIVE][ONE]))
      p->bundle[NEGATIVE][TWO] = my_max(p->bundle[NEGATIVE][TWO], cur_val * p->bundle[NEGATIVE][ONE]);
    p->bundle[POSITIVE][ONE] = my_max(p->bundle[POSITIVE][ONE], cur_val);
  } else { // cur_val is -ve
    if (validate(p->bundle[POSITIVE][ONE]))
      p->bundle[NEGATIVE][TWO] = my_max(p->bundle[NEGATIVE][TWO], cur_val * p->bundle[POSITIVE][ONE]);
    if (validate(p->bundle[NEGATIVE][ONE]))
      p->bundle[POSITIVE][TWO] = my_max(p->bundle[POSITIVE][TWO], cur_val * p->bundle[NEGATIVE][ONE]);
    p->bundle[NEGATIVE][ONE] = my_max(p->bundle[NEGATIVE][ONE], cur_val);
  }
}
void updateAns(long a) {
  if (ans == INVALID) ans = a;
  else ans = max(ans, a);
}
void solve() {
  block_size = ceil(sqrt(n));
  merge_sort(1, n);
  long prev = INVALID;
  int cur_val;
  for (int i = 1; i <= n; i++) {
    cur_val = profits[indices[i]].val;
    if (prev == cur_val) {
      continue;
    } else prev = cur_val;
    resetBlank();
    fillBlank(indices[i], cur_val);
    if (min_values[NEGATIVE] != INVALID) updateAns(cur_val * min_values[NEGATIVE]);
    if (min_values[POSITIVE] != INVALID) updateAns(cur_val * min_values[POSITIVE]);
    min_values[POSITIVE] = min(min_values[POSITIVE], min(blank.bundle[POSITIVE][TWO], cur_val * blank.bundle[POSITIVE][ONE]));
    if (validate(blank.bundle[POSITIVE][TWO])) {
      updateAns(cur_val * blank.bundle[POSITIVE][TWO]);
    }
    if (validate(blank.bundle[NEGATIVE][TWO])) {
      updateAns(cur_val * blank.bundle[NEGATIVE][TWO]);
      if (min_values[NEGATIVE] != INVALID)
        min_values[NEGATIVE] = min(min_values[NEGATIVE], blank.bundle[NEGATIVE][TWO]);
      else min_values[NEGATIVE] = blank.bundle[NEGATIVE][TWO];
    }
    addToBlock(indices[i], cur_val);
  }
}
long maximumProfit(vector<int> p) {
  reset();
  for (vector<int>::iterator it = p.begin(); it != p.end(); it++) {
    ++n;
    indices[n] = n;
    profits[n].val = *it;
  }
  solve();
  return ans == INVALID ? -1 : ans;
}
void program() {
  reset();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%ld", &profits[i].val);
    indices[i] = i;
  }
  solve();
  printf("%ld\n", ans == INVALID ? -1 : ans);
}
int main() {
  freopen("HackerRank/MaximizingTheProfit_input.txt", "r", stdin);
  program();
  return 0;
}
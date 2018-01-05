// AC - Square Root Decomposition, Extreme precomputation - F yeaaaaaaaaaaaaaaaaaaahhhhhhhhhhhhhhhhhhh!
#include <bits/stdc++.h>
#define N_MAX 100010
#define VAL_MAX 100010
#define BLOCK_MAX 500
#define val(i) a[i]
using namespace std;
int next_ptr[N_MAX], prev_ptr[N_MAX], last_ptr[VAL_MAX];
int n, m, a[N_MAX], block_size, block_count;
int precomputed_ans[BLOCK_MAX][N_MAX], last_in_block[BLOCK_MAX][VAL_MAX];
int getBlockNumber(int i) { return ((i - 1) / block_size) + 1; }
int getBlockLeft(int blk_id) { return ((blk_id - 1) * block_size) + 1; }
int getBlockRight(int blk_id) { return min(blk_id * block_size, n); }
class {
  int cur_time;
  int stored_val[N_MAX];
  int last_seen[N_MAX];
public:
  void clear() { cur_time++; }
  int peek(int val) {
    if (last_seen[val] == cur_time)
      return stored_val[val];
    else return 0;
  }
  int set(int val, int idx) {
    stored_val[val] = idx;
    last_seen[val] = cur_time;
  }
} lazyMap;
void preprocess() {
  int l, r, ans, last;
  for (int blk = 1; blk <= block_count; blk++) {
    lazyMap.clear();
    ans = 0;
    l = getBlockLeft(blk);
    r = n;
    for (int i = l; i <= r; i++) {
      last = lazyMap.peek(val(i));
      if (last) // seen already
        ans = max(ans, i - last);
      else lazyMap.set(val(i), i);
      precomputed_ans[blk][i] = ans;
    }
    for (int val = 1; val <= m; val++)
      if (!last_in_block[blk][val])
        last_in_block[blk][val] = last_in_block[blk - 1][val];
  }
}
int solve(int l, int r) {
  int blk_l = getBlockNumber(l);
  int blk_l_s = getBlockLeft(blk_l);
  int blk_l_e = getBlockRight(blk_l);
  if (blk_l_s == l)
    return precomputed_ans[blk_l][r];
  int ans = 0, blk_r = getBlockNumber(r), ptr;
  if (r <= blk_l_e) {
    lazyMap.clear();
    for (int i = l; i <= r; i++) {
      ptr = lazyMap.peek(val(i));
      if (ptr)
        ans = max(ans, i - ptr);
      else lazyMap.set(val(i), i);
    }
  } else {
    for (int i = l; i <= blk_l_e; i++) {
      if (prev_ptr[i] < l) { // encountering it first
        ptr = last_in_block[blk_r - 1][val(i)];
        while (ptr <= r) {
          ans = max(ans, ptr - i);
          ptr = next_ptr[ptr];
        }
      }
    }
    ans = max(ans, precomputed_ans[blk_l + 1][r]);
  }
  return ans;
}
void program() {
  int k, l, r;
  scanf("%d %d %d", &n, &m, &k);
  block_size = ceil(sqrt(n));
  block_count = getBlockNumber(n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    prev_ptr[i] = last_ptr[val(i)];
    next_ptr[i] = n + 1;
    if (last_ptr[val(i)] != 0)
      next_ptr[last_ptr[val(i)]] = i;
    last_ptr[val(i)] = i;
    last_in_block[getBlockNumber(i)][val(i)] = i;
  }
  preprocess();
  for (int i = 1; i <= k; i++) {
    scanf("%d %d", &l, &r);
    printf("%d\n", solve(l, r));
  }
}
int main() {
  program();
  return 0;
}
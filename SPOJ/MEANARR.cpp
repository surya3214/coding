// AC Mothafookin Ayyyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#pragma GCC optimize "O3"
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 200000
#define BLOCKS_SIZE 448
#define BLOCKS_MAX 448
using namespace std;
typedef long long int ll;
int input[BUFF(N_MAX)];
int n, k;
ll t_rep[BUFF(N_MAX)], t_rep_sorted[BUFF(N_MAX)];
ll diffs[BUFF(N_MAX)];
int d_ptr;
struct {
  int val;
} blocks[BUFF(BLOCKS_MAX)]; // blocks[] covers invalids[]
int block_size;
int invalids[BUFF(N_MAX)]; // only represents the positions of items in diffs
int getBlockNumber(int i) { return (i - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(d_ptr, blk_id * block_size); }
int getSquareRootOf(int x) {
  int i = 2;
  while (i * i <= x) ++i;
  return --i;
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int findBS(ll val) {
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (t_rep_sorted[mid] >= val)
      r = mid - 1;
    else l = mid + 1;
  }
  return n - r;
}
int findPositionInDiff(ll x) {
  int l, r, mid;
  l = 1, r = d_ptr;
  while (l <= r) {
    mid = getMid(l, r);
    if (diffs[mid] == x) return mid;
    else if (diffs[mid] > x) r = mid - 1;
    else l = mid + 1;
  }
}
void process() {
  diffs[++d_ptr] = t_rep_sorted[1];
  for (int i = 2; i <= n; ++i) {
    if (t_rep_sorted[i] != diffs[d_ptr])
      diffs[++d_ptr] = t_rep_sorted[i]; // contains unique diffs in sorted order
  }
  block_size = BLOCKS_SIZE;
}
void addToBlock(int blk_id, int val) { blocks[blk_id].val += val; }
void considerInvalid(ll val) {
  int idx = findPositionInDiff(val);
  ++invalids[idx];
  for (int blk_id = getBlockNumber(idx); blk_id >= 1; --blk_id)
    addToBlock(blk_id, 1);
}
int countInvalid(ll val) {
  int l, r;
  l = findPositionInDiff(val), r = d_ptr;
  int blk_id, blk_l, blk_r, cnt;
  cnt = 0;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    if (l == blk_l && blk_r <= r) {
      cnt += blocks[blk_id].val;
      l = r + 1;
    } else {
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i)
        cnt += invalids[i];
      l = t_r + 1;
    }
  }
  return cnt;
}
void program() {
  ll cnt = 0;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i]);
    t_rep_sorted[i] = t_rep[i] = (ll) input[i] - k + t_rep[i - 1];
  }
  sort(t_rep_sorted + 1, t_rep_sorted + 1 + n);
  process();
  for (int i = 1; i <= n; ++i) {
    cnt += findBS(t_rep[i - 1]) - ((i > 1) ? countInvalid(t_rep[i - 1]) : 0);
    considerInvalid(t_rep[i]);
  }
  printf("%lld\n", cnt);
}
int main() {
  program();
  return 0;
}
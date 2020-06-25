// AC #SquareRootDecomposition, #Hard
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
const int BLOCKS_MAX = 448;
const int N_MAX = 2e5;
int n, q;
ll ans;
int in[BUFF(N_MAX)];
struct {
  int l, r;
  ll increasing, alternating;
} blocks[BUFF(BLOCKS_MAX)];
int blk_cnt, blk_size;
int getBlockId(int idx) { return ((idx - 1) / blk_size) + 1; }
void resetBlocks() {
  // blk_cnt = ceil(n / blk_size);
  blk_size = ceil(sqrt(n));
  blk_cnt = getBlockId(n);
  for (int blk_id = 1; blk_id <= blk_cnt; ++blk_id) {
    blocks[blk_id].l = blocks[blk_id - 1].r + 1;
    blocks[blk_id].r = min(n, blocks[blk_id].l + blk_size - 1);
    blocks[blk_id].increasing = blocks[blk_id].alternating = 0;
  }
}
void updatePos(int pos, int val) {
  int blk_id = getBlockId(pos);
  int local = pos - blocks[blk_id - 1].r;
  int t = (local & 1) ? in[pos] : -in[pos];
  blocks[blk_id].increasing -= t * local;
  blocks[blk_id].alternating -= t;
  in[pos] = val;
  t = (local & 1) ? in[pos] : -in[pos];
  blocks[blk_id].increasing += t * local;
  blocks[blk_id].alternating += t;
}
ll queryAns(int l, int r) {
  ll ret = 0, sum;
  int blk_id = getBlockId(l);
  int local = 1;
  while (l <= r) {
    if (blocks[blk_id].l == l && blocks[blk_id].r <= r) {
      sum = blocks[blk_id].increasing +
          (local - 1) * blocks[blk_id].alternating;
      if (local & 1)
        ret += sum;
      else ret -= sum;
      local += blk_size;
    } else {
      for (int i = l; i <= min(r, blocks[blk_id].r); ++i, ++local) {
        sum = 1LL * in[i] * local;
        if (local & 1)
          ret += sum;
        else ret -= sum;
      }
    }
    l = blocks[blk_id].r + 1;
    ++blk_id;
  }
  return ret;
}
void program() {
  int tcase;
  char op;
  cin >> tcase;
  for (int t = 1; t <= tcase; ++t) {
    ans = 0;
    cin >> n >> q;
    resetBlocks();
    for (int i = 1, t, blk_id = 1, local = 1; i <= n; ++i) {
      cin >> in[i];
      t = (local & 1) ? in[i] : -in[i];
      blocks[blk_id].increasing += 1LL * t * local;
      blocks[blk_id].alternating += t;
      if (local == blk_size) {
        ++blk_id;
        local = 1;
      } else ++local;
    }
    for (int i = 1, x, y; i <= q; ++i) {
      cin >> op >> x >> y;
      if (op == 'U') // update
        updatePos(x, y);
      else // query
        ans += queryAns(x, y);
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
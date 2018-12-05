// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (3 * 1e5)
#define BLOCKS_MAX 1000 // 550
#define BLOCKS_SIZE 250 // 550
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct S {
  int height;
  int index;
} s[BUFF(N_MAX)];
int s_ptr;
struct Q {
  int l, r;
  ll x;
  int index;
  bool solved;
} queries[BUFF(N_MAX)];
int ans[BUFF(N_MAX)];
int n, m;
bool s_comparator(S a, S b) { return a.height < b.height; }
bool q_comparator(Q a, Q b) { return a.x < b.x; }
struct L {
  int index;
  struct L *next;
} nodes_pool[BUFF(N_MAX)], *front, *rear;
int n_ptr;
struct {
  int h;
  int starts_at;
  int ends_at;
  ll sum;
} positions[BUFF(N_MAX)];
struct {
  int blk_l, blk_r;
  ll maximum_power_in_block;
} blocks[BUFF(BLOCKS_MAX)];
int block_count, block_size;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
void updateStartsAt(int idx) {
  int x = positions[idx].starts_at;
  while (positions[x].starts_at != x)
    x = positions[x].starts_at;
  positions[idx].starts_at = x;
}
void updateEndsAt(int idx) {
  int x = positions[idx].ends_at;
  while (positions[x].ends_at != x)
    x = positions[x].ends_at;
  positions[idx].ends_at = x;
}
void updatePositions(int idx) { // updates only starts_at & ends_at, query ends_at cell to extract the correct sum
  updateStartsAt(idx);
  updateEndsAt(idx);
}
ll calculatePower(int len, ll sum) { return 1LL * 2 * len * sum; }
void addToPositions(int h, int idx) {
  positions[idx].h = positions[idx].sum = h;
  positions[idx].starts_at = positions[idx].ends_at = idx;
  int blk_id = getBlockNumber(idx);
  if (idx != blocks[blk_id].blk_l && positions[idx - 1].h) {
    updateStartsAt(idx - 1);
    positions[idx].starts_at = positions[idx - 1].starts_at;
    positions[positions[idx].starts_at].ends_at = idx;
    positions[idx].sum += positions[idx - 1].sum;
  }
  if (idx != blocks[blk_id].blk_r && positions[idx + 1].h) {
    updateEndsAt(idx + 1);
    positions[idx].ends_at = positions[idx + 1].ends_at;
    positions[positions[idx].ends_at].starts_at = positions[idx].starts_at;
    positions[positions[idx].ends_at].sum += positions[idx].sum;
  }
  int end = positions[idx].ends_at;
  ll power = calculatePower(positions[end].ends_at - positions[end].starts_at + 1, positions[end].sum);
  blocks[blk_id].maximum_power_in_block = max(blocks[blk_id].maximum_power_in_block, power);
}
void moveSPtr() {
  int val = s[s_ptr + 1].height;
  while (s_ptr + 1 <= n && s[s_ptr + 1].height == val) {
    ++s_ptr;
    addToPositions(s[s_ptr].height, s[s_ptr].index);
  }
}
ll getMaximumPowerInRange(int l, int r) {
  int blk_id, blk_l, blk_r;
  ll power, sum;
  int starts_at, ends_at;
  starts_at = ends_at = power = sum = 0;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    if (l == blk_l && blk_r <= r) {
      power = max(power, blocks[blk_id].maximum_power_in_block);
      if (sum && positions[blk_l].h) {
        updateEndsAt(blk_l);
        power = max(power, calculatePower(positions[blk_l].ends_at - starts_at + 1, sum + positions[positions[blk_l].ends_at].sum));
      }
      // update meta data for the next block
      if (!positions[blk_r].h)
        sum = 0;
      else {
        updateStartsAt(blk_r);
        ends_at = blk_r;
        if (positions[ends_at].starts_at != blk_l) {
          starts_at = positions[ends_at].starts_at;
          sum = positions[ends_at].sum;
        } else {
          if (sum)
            sum += positions[ends_at].sum;
          else {
            sum = positions[ends_at].sum;
            starts_at = blk_l;
          }
        }
      }
      l = blk_r + 1;
    } else {
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i) {
        if (!positions[i].h) {
          sum = 0;
        } else {
          ends_at = i;
          if (sum)
            sum += positions[i].h;
          else {
            sum = positions[i].h;
            starts_at = i;
          }
          power = max(power, calculatePower(ends_at - starts_at + 1, sum));
        }
      }
      l = t_r + 1;
    }
  }
  return power;
}
/*
void processQueries() {
  ll ret = getMaximumPowerInRange(1, n);
  ll x;
  int i;
  struct L *t, *prev = NULL;
  t = front;
  while (t) {
    i = t->index;
    if (queries[i].x > ret)
      break;
    x = getMaximumPowerInRange(queries[i].l, queries[i].r);
    if (x >= queries[i].x) {
      ans[queries[i].index] = s[s_ptr].height;
      if (!prev)
        front = front->next;
      else prev->next = t->next;
    }
    prev = t;
    t = t->next;
  }
}
*/
void processQueries() {
  ll ret = getMaximumPowerInRange(1, n);
  ll x;
  for (int i = 1; i <= m; ++i) {
    if (queries[i].x > ret)
      break;
    if (!queries[i].solved) {
      x = getMaximumPowerInRange(queries[i].l, queries[i].r);
      if (x >= queries[i].x) {
        ans[queries[i].index] = s[s_ptr].height;
        queries[i].solved = true;
      }
    }
  }
}
void solve() {
  while (s_ptr < n) {
    moveSPtr();
    processQueries();
  }
}
void initBlocks() {
  block_size = BLOCKS_SIZE;
  block_count = getBlockNumber(n);
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
  }
}
void createList() {
  struct L *t;
  for (int i = 1; i <= m; ++i) {
    t = &nodes_pool[i];
    t->index = i;
    if (rear) {
      rear->next = t;
      rear = t;
    } else front = rear = t;
  }    
}
void program() {
  scanf("%d %d", &n, &m);
  initBlocks();
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &s[i].height);
    s[i].index = i;
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d %lld", &queries[i].l, &queries[i].r, &queries[i].x);
    queries[i].index = i;
    ans[i] = -1;
  }
  sort(s + 1, s + 1 + n, s_comparator);
  sort(queries + 1, queries + 1 + m, q_comparator);
  createList();
  solve();
  for (int i = 1; i <= m; ++i)
    printf("%d\n", ans[i]);
}
int main() {
  freopen("HackerRank/BasketballTournament_input.txt", "r", stdin);
  program();
  return 0;
}
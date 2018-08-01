// AC - Mo's Algorithm
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define VAL_MAX 100001
#define BLOCKS_SIZE 317
#define BLOCKS_MAX 317
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n, q;
int t_l, t_r;
int input[BUFF(N_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int counts[BUFF(VAL_MAX)];
int frequency[BUFF(VAL_MAX)];
struct Q {
  int l, r;
  int idx;
} query[BUFF(N_MAX)];
int ans[BUFF(N_MAX)];
int t_ans;
bool m_comparator(Q a, Q b) {
  int a_blk, b_blk;
  a_blk = getBlockNumber(a.l);
  b_blk = getBlockNumber(b.l);
  if (a_blk != b_blk)
    return a_blk < b_blk;
  return a.r < b.r;
}
void add(int val) {
  --frequency[counts[val]];
  ++frequency[++counts[val]];
  t_ans = max(t_ans, counts[val]);
}
void remove(int val) {
  --frequency[counts[val]];
  ++frequency[--counts[val]];
  if (!frequency[t_ans])
    --t_ans;
}
void move(int l, int r) {
  // move t_l to l
  if (t_l < l) {
    for (int i = t_l; i < l; ++i)
      remove(input[i]);
  }
  else if (l < t_l) {
    for (int i = t_l - 1; i >= l; --i)
      add(input[i]);
  }
  // move t_r to r
  if (t_r < r) {
    for (int i = t_r + 1; i <= r; ++i)
      add(input[i]);
  }
  else if (r < t_r) {
    for (int i = t_r; i > r; --i)
      remove(input[i]);
  }
  t_l = l, t_r = r;
}
void solve() {
  t_l = t_r = t_ans = 0;
  for (int i = 1; i <= q; ++i) {
    move(query[i].l, query[i].r);
    ans[query[i].idx] = t_ans;
  }
}
void program() {
  scanf("%d %d", &n, &q);
  block_size = BLOCKS_SIZE;
  block_count = getBlockNumber(VAL_MAX);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i]);
    ++input[i];
  }
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &query[i].l, &query[i].r);
    ++query[i].l, ++query[i].r;
    query[i].idx = i;
  }
  sort(query + 1, query + 1 + q, m_comparator);
  solve();
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
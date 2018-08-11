// AC Mo's Algorithm
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 200000
#define BLOCKS_SIZE 500
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n, q;
int input[BUFF(N_MAX)];
int sorted_input[BUFF(N_MAX)];
bool ans[BUFF(N_MAX)];
int frequency[BUFF(N_MAX)];
int counts[BUFF(N_MAX)];
struct Q {
  int l, r, k, idx;
} query[BUFF(N_MAX)];
int block_size, t_l, t_r, t_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
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
  if (!t_count || counts[val] > t_count) t_count = counts[val];
}
void remove(int val) {
  --frequency[counts[val]];
  ++frequency[--counts[val]];
  if (!frequency[t_count]) --t_count;
}
void move(int l, int r) {
  // move t_l to l
  if (t_l < l) {
    for (int i = t_l; i < l; ++i)
      remove(input[i]);
  } else if (l < t_l) {
    for (int i = t_l - 1; i >= l; --i)
      add(input[i]);
  }
  // move t_r to r
  if (t_r < r) {
    for (int i = t_r + 1; i <= r; ++i)
      add(input[i]);
  } else if (r < t_r) {
    for (int i = t_r; i > r; --i)
      remove(input[i]);
  }
  t_l = l, t_r = r;
}
void solve() {
  t_l = t_r = t_count = 0;
  for (int i = 1; i <= q; ++i) {
    move(query[i].l, query[i].r);
    if ((ll) t_count * query[i].k >= query[i].r - query[i].l + 1)
      ans[query[i].idx] = true;
    else ans[query[i].idx] = false;
  }
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int findBS(int x) {
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (sorted_input[mid] == x)
      return mid;
    else if (sorted_input[mid] < x)
      l = mid + 1;
    else r = mid - 1;
  }
}
void program() {
  scanf("%d %d", &n, &q);
  block_size = BLOCKS_SIZE;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i]);
    sorted_input[i] = input[i];
  }
  sort(sorted_input + 1, sorted_input + 1 + n);
  for (int i = 1; i <= n; ++i)
    input[i] = findBS(input[i]);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %d", &query[i].l, &query[i].r, &query[i].k);
    query[i].idx = i;
  }
  sort(query + 1, query + 1 + q, m_comparator);
  solve();
  for (int i = 1; i <= q; ++i)
    if (ans[i]) printf("YES\n");
    else printf("NO\n");
}
int main() {
  program();
  return 0;
}
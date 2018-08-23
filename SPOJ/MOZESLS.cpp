// AC - Mo's Algorithm
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100
#define Q_MAX 50
#define BLOCKS_SIZE 10
// #pragma GCC optimize "O4"
using namespace std;
int block_size, block_count;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  int SMS;
  int SM;
  int MS;
  int S;
  int M;
} cnt;
char str[BUFF(N_MAX)];
int q;
struct Q {
  int idx, l, r;
} query[BUFF(Q_MAX)];
int ans[BUFF(Q_MAX)];
int t_l, t_r;
void addL(int i) {
  if (i < 0) return;
  if (str[i] == 's') {
    ++cnt.S;
    cnt.SM += cnt.M;
    cnt.SMS += cnt.MS;
  } else if (str[i] == 'm') {
    ++cnt.M;
    cnt.MS += cnt.S;
  }
}
void removeL(int i) {
  if (i < 0) return;
  if (str[i] == 's') {
    --cnt.S;
    cnt.SM -= cnt.M;
    cnt.SMS -= cnt.MS;
  } else if (str[i] == 'm') {
    --cnt.M;
    cnt.MS -= cnt.S;
  }
}
void addR(int i) {
  if (i < 0) return;
  if (str[i] == 's') {
    ++cnt.S;
    cnt.MS += cnt.M;
    cnt.SMS += cnt.SM;
  } else if (str[i] == 'm') {
    ++cnt.M;
    cnt.SM += cnt.S;
  }
}
void removeR(int i) {
  if (i < 0) return;
  if (str[i] == 's') {
    --cnt.S;
    cnt.MS -= cnt.M;
    cnt.SMS -= cnt.SM;
  } else if (str[i] == 'm') {
    --cnt.M;
    cnt.SM -= cnt.S;
  }
}
void move(int l, int r) {
  // move t_r to r
  if (t_r < r) {
    for (int i = t_r + 1; i <= r; ++i)
      addR(i);
  } else if (r < t_r) {
    for (int i = t_r; i > r; --i)
      removeR(i);
  }
  // move t_l to l
  if (t_l < l) {
    for (int i = t_l; i < l; ++i)
      removeL(i);
  } else if (l < t_l) {
    for (int i = t_l - 1; i >= l; --i)
      addL(i);
  }
  t_l = l, t_r = r;
}
void compute() {
  t_l = t_r = -1;
  for (int i = 1; i <= q; ++i) {
    move(query[i].l - 1, query[i].r - 1);
    ans[query[i].idx] = cnt.SMS;
  }
}
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
bool m_comparator(Q a, Q b) {
  int a_blk, b_blk;
  a_blk = getBlockNumber(a.l);
  b_blk = getBlockNumber(b.l);
  if (a_blk != b_blk)
    return a_blk < b_blk;
  return a.r < b.r;
}
void program() {
  block_size = BLOCKS_SIZE;
  scanf("%s", str);
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &query[i].l, &query[i].r);
    query[i].idx = i;
  }
  sort(query + 1, query + 1 + q, m_comparator);
  compute();
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define K_MAX 20
#define INF 1e9
#define BLOCKS_MAX 317
using namespace std;
typedef long long int ll;
int n;
struct {
  int l, r;
} ranges[BUFF(N_MAX)];
int sorted_indices[BUFF(N_MAX)];
struct {
  int count;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
struct {
  int t1, t2;
  int e1, e2;
  int buff1[BUFF(N_MAX / 2)], buff2[BUFF(N_MAX / 2)];
} m_buffer;
int getSquareNumberOf(int x) {
  int i = 2;
  while (i * i <= x) ++i;
  return i - 1;
}
int getBlockNumber(int i) { return (i - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(n, blk_id * block_size); }
int queries[BUFF(K_MAX)];
int k;
int getMid(int l, int r) { return l + (r - l) / 2; }
void copyToBuffer(int s1, int e1, int s2, int e2) {
  m_buffer.e1 = m_buffer.e2 = 0;
  for (int i = s1; i <= e1; ++i)
    m_buffer.buff1[m_buffer.e1++] = sorted_indices[i];
  for (int i = s2; i <= e2; ++i)
    m_buffer.buff2[m_buffer.e2++] = sorted_indices[i];
}
void fillArrayFromBuffer(int pos) {
  m_buffer.t1 = m_buffer.t2 = 0;
  int a, b;
  while (m_buffer.t1 < m_buffer.e1 && m_buffer.t2 < m_buffer.e2) {
    a = m_buffer.buff1[m_buffer.t1], b = m_buffer.buff2[m_buffer.t2];
    if (ranges[a].l < ranges[b].l ||
       (ranges[a].l == ranges[b].l && ranges[a].r < ranges[b].r)) {
      sorted_indices[pos++] = a;
      ++m_buffer.t1;
    } else {
      sorted_indices[pos++] = b;
      ++m_buffer.t2;
    }
  }
  while (m_buffer.t1 < m_buffer.e1)
    sorted_indices[pos++] = m_buffer.buff1[m_buffer.t1++];
  while (m_buffer.t2 < m_buffer.e2)
    sorted_indices[pos++] = m_buffer.buff2[m_buffer.t2++];
}
void merge(int s1, int e1, int e2) {
  int s2 = e1 + 1;
  copyToBuffer(s1, e1, s2, e2);
  fillArrayFromBuffer(s1);
}
void merge_sort(int l, int r) {
  if (l < r) {
    int mid = getMid(l, r);
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);
  }
}
int findMinimumInK() {
  struct {
    int val;
    int idx;
  } t_min;
  t_min.val = INF;
  for (int i = 0; i <= k; ++i) {
    if (queries[i] < t_min.val) {
      t_min.val = queries[i];
      t_min.idx = i;
    }
  }
  queries[t_min.idx] = INF;
  return t_min.val;
}
int findBS(int x) {
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (ranges[sorted_indices[mid]].l >= x)
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
int findCountInRange(int l, int r) {
  if (r < l) return 0;
  int ptr = findBS(l);
  if (ptr == n + 1) return 0;
  int cnt = 0;
  while (ptr <= n && ranges[sorted_indices[ptr]].l <= r) {
    if (ranges[sorted_indices[ptr]].r <= r) ++cnt;
    ++ptr;
  }
  return cnt;
}
void preprocess() {
  int blk_l, blk_r;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blk_l = getBlockLeft(blk_id);
    blk_r = getBlockRight(blk_id);
    for (int i = blk_l; i <= blk_r; ++i)
  }
}
void program() {
  int q, l, r;
  int ans;
  int processed;
  scanf("%d", &n);
  block_size = getSquareNumberOf(n);
  block_count = getBlockNumber(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &ranges[i].l, &ranges[i].r);
    sorted_indices[i] = i;
  }
  merge_sort(1, n);
  preprocess();
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &k);
    for (int j = 1; j <= k; ++j)
      scanf("%d", &queries[j]);
    queries[0] = 0;
    ans = n;
    processed = 0;
    while (processed <= k) {
      l = findMinimumInK();
      r = findMinimumInK();
      ans -= findCountInRange(l + 1, r - 1);
      ++processed;
    }
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
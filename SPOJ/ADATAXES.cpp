// AC Phew! Square Root Decomposition, sqrt(n) gives TLE; Manual merge sort also gives TLE. Weird!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (3 * 1e5)
#define Q_MAX (int) (3 * 1e5)
#define MOD 1000000007
#define BLOCKS_MAX 500
#define BLOCKS_SIZE 1000
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, q;
struct E {
  int val;
  int l, r, idx;
} n_events[BUFF(N_MAX)], q_events[BUFF(Q_MAX)];
int n_ptr;
struct {
  bool inited;
  ll product;
  int blk_l, blk_r;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(N_MAX, blk_id * block_size); }
int numbers[BUFF(N_MAX)];
int ans[BUFF(Q_MAX)];
bool m_comparator(E a, E b) { return a.val < b.val; }
void sanitizeBlock(int blk_id) {
  if (!blocks[blk_id].inited) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
    blocks[blk_id].product = 1;
    blocks[blk_id].inited = true;
  }
}
void t_mod(ll &x) {
  if (x >= MOD)
    x %= MOD;
}
void addToBlocks(int idx, int val) {
  numbers[idx] = val;
  int blk_id = getBlockNumber(idx);
  sanitizeBlock(blk_id);
  blocks[blk_id].product *= val;
  t_mod(blocks[blk_id].product);
}
int getProductIn(int l, int r) {
  ll p = 1;
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    sanitizeBlock(blk_id);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    if (l == blk_l && blk_r <= r) {
      p *= blocks[blk_id].product;
      t_mod(p);
      l = blk_r + 1;
    } else {
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i) {
        if (numbers[i]) {
          p *= numbers[i];
          t_mod(p);
        }
      }
      l = t_r + 1;
    }
  }
  t_mod(p);
  return p;
}
void addUntil(int val) {
  while (n_ptr <= n && n_events[n_ptr].val <= val) {
    addToBlocks(n_events[n_ptr].idx, n_events[n_ptr].val);
    ++n_ptr;
  }
}
void program() {
  int x;
  scanf("%d %d", &n, &q);
  block_size = BLOCKS_SIZE;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &n_events[i].val);
    n_events[i].idx = i;
  }
  sort(n_events + 1, n_events + 1 + n, m_comparator);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %d", &q_events[i].l, &q_events[i].r, &q_events[i].val);
    ++q_events[i].l;
    ++q_events[i].r;
    q_events[i].idx = i;
  }
  sort(q_events + 1, q_events + 1 + q, m_comparator);
  n_ptr = 1;
  for (int i = 1; i <= q; ++i) {
    addUntil(q_events[i].val);
    ans[q_events[i].idx] = getProductIn(q_events[i].l, q_events[i].r);
  }
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
/*
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (3 * 1e5)
#define Q_MAX (int) (3 * 1e5)
#define MOD 1000000007
#define BLOCKS_MAX 500
#define BLOCKS_SIZE 1000
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, q;
struct E {
  int val;
  int l, r, idx;
} n_events[BUFF(N_MAX)], q_events[BUFF(Q_MAX)];
int sorted_n[BUFF(N_MAX)], sorted_q[BUFF(Q_MAX)];
int n_ptr;
struct {
  bool inited;
  ll product;
  int blk_l, blk_r;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(N_MAX, blk_id * block_size); }
int numbers[BUFF(N_MAX)];
int ans[BUFF(Q_MAX)];
bool m_comparator(E a, E b) { return a.val < b.val; }
void sanitizeBlock(int blk_id) {
  if (!blocks[blk_id].inited) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
    blocks[blk_id].product = 1;
    blocks[blk_id].inited = true;
  }
}
void t_mod(ll &x) {
  if (x >= MOD)
    x %= MOD;
}
void addToBlocks(int idx, int val) {
  numbers[idx] = val;
  int blk_id = getBlockNumber(idx);
  sanitizeBlock(blk_id);
  blocks[blk_id].product *= val;
  t_mod(blocks[blk_id].product);
}
int getProductIn(int l, int r) {
  ll p = 1;
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    sanitizeBlock(blk_id);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    if (l == blk_l && blk_r <= r) {
      p *= blocks[blk_id].product;
      t_mod(p);
      l = blk_r + 1;
    } else {
      int t_r = min(r, blk_r);
      for (int i = l; i <= t_r; ++i) {
        if (numbers[i]) {
          p *= numbers[i];
          t_mod(p);
        }
      }
      l = t_r + 1;
    }
  }
  t_mod(p);
  return p;
}
void addUntil(int val) {
  int x;
  while (n_ptr <= n) {
    x = sorted_n[n_ptr];
    if (n_events[x].val <= val) {
      addToBlocks(n_events[x].idx, n_events[x].val);
      ++n_ptr;
    } else return;
  }
}
struct {
  int t1, t2;
  int e1, e2;
  int buff1[BUFF(N_MAX / 2)], buff2[BUFF(N_MAX / 2)];
  bool type;
} m_buffer;
int getMid(int l, int r) { return l + (r - l) / 2; }
void copyToBuffer(int &s1, int &e1, int &s2, int &e2) {
  int *p;
  if (m_buffer.type)
    p = sorted_q;
  else p = sorted_n;
  m_buffer.e1 = m_buffer.e2 = 0;
  for (int i = s1; i <= e1; i++)
    m_buffer.buff1[m_buffer.e1++] = p[i];
  for (int i = s2; i <= e2; i++)
    m_buffer.buff2[m_buffer.e2++] = p[i];
}
void fillArrayFromBuffer(int &ptr) {
  struct E *p;
  if (m_buffer.type)
    p = q_events;
  else p = n_events;
  int *q;
  if (m_buffer.type)
    q = sorted_q;
  else q = sorted_n;
  m_buffer.t1 = m_buffer.t2 = 0;
  while (m_buffer.t1 < m_buffer.e1 && m_buffer.t2 < m_buffer.e2) {
    if (p[m_buffer.buff1[m_buffer.t1]].val <= p[m_buffer.buff2[m_buffer.t2]].val)
      q[ptr++] = m_buffer.buff1[m_buffer.t1++];
    else q[ptr++] = m_buffer.buff2[m_buffer.t2++];
  }
  while (m_buffer.t1 < m_buffer.e1)
    q[ptr++] = m_buffer.buff1[m_buffer.t1++];
  while (m_buffer.t2 < m_buffer.e2)
    q[ptr++] = m_buffer.buff2[m_buffer.t2++];
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
void program() {
  int x;
  scanf("%d %d", &n, &q);
  block_size = BLOCKS_SIZE;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &n_events[i].val);
    n_events[i].idx = i;
    sorted_n[i] = i;
  }
  merge_sort(1, n);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %d", &q_events[i].l, &q_events[i].r, &q_events[i].val);
    ++q_events[i].l;
    ++q_events[i].r;
    q_events[i].idx = i;
    sorted_q[i] = i;
  }
  m_buffer.type = true;
  merge_sort(1, q);
  n_ptr = 1;
  for (int i = 1; i <= q; ++i) {
    x = sorted_q[i];
    addUntil(q_events[x].val);
    ans[q_events[x].idx] = getProductIn(q_events[x].l, q_events[x].r);
  }
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
*/
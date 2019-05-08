// RTE
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define Q_MAX 5000
#define K_MAX 20
#define INTERVALS_MAX (10 * (BUFF(K_MAX) * BUFF(Q_MAX)))
#define POINTS_MAX (int) (10 * (1e5 + (INTERVALS_MAX)))
#define BLOCK_SIZE 350
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, q, INF;
struct Q {
  int k, ans;
  int aliens[BUFF(K_MAX)];
} queries[BUFF(Q_MAX)];
struct P {
  int id, val, m_id;
  bool type; // true if an interval; false for points
  bool is_start; // valid only if |type| is true; true for s, false for e
} points[BUFF(POINTS_MAX)];
int p_ptr;
struct I {
  int q_id, s, e;
  int p_s, p_e;
} intervals[BUFF(INTERVALS_MAX)];
int i_ptr, block_size;
void addToPoints(int s, int e, int id, bool type, int m_id = 0) {
  ++p_ptr;
  points[p_ptr].type = type;
  points[p_ptr].id = id;
  points[p_ptr].val = s;
  points[p_ptr].is_start = true;
  points[p_ptr].m_id = m_id;
  ++p_ptr;
  points[p_ptr].type = type;
  points[p_ptr].id = id;
  points[p_ptr].val = e;
  points[p_ptr].is_start = false;
  points[p_ptr].m_id = m_id;
}
void addToIntervals(int q_id, int s, int e) {
  if (s >= e)
    return;
  ++i_ptr;
  intervals[i_ptr].q_id = q_id;
  intervals[i_ptr].s = s;
  intervals[i_ptr].e = e;
  addToPoints(s, e, q_id, false, i_ptr);
}
void generateIntervals() {
  int l, r;
  for (int i = 1; i <= q; ++i) {
    sort(queries[i].aliens + 1, queries[i].aliens + 1 + queries[i].k);
    addToIntervals(i, 1, queries[i].aliens[1] - 1);
    for (int j = 1; j < queries[i].k; ++j) {
      l = queries[i].aliens[j] + 1;
      r = queries[i].aliens[j + 1] - 1;
      addToIntervals(i, l, r);
    }
    addToIntervals(i, queries[i].aliens[queries[i].k] + 1, INF);
  }
}
bool i_comparator(I a, I b) {
  int a_blk = a.p_s / block_size;
  int b_blk = b.p_s / block_size;
  if (a_blk != b_blk)
    return a_blk < b_blk;
  return a.p_e < b.p_e;
}
void sortIntervalsbyMosAlgorithm() {
  block_size = ceil(sqrt(p_ptr));
  // block_size = BLOCK_SIZE;
  sort(intervals + 1, intervals + 1 + i_ptr, i_comparator);
}
bool p_comparator(P a, P b) { return a.val < b.val; }
void sortAllPoints() {
  sort(points + 1, points + 1 + p_ptr, p_comparator);
}
int t_ans, t_l, t_r;
bool started[BUFF(POINTS_MAX)], ended[BUFF(POINTS_MAX)];
void add(int p_id) {
  if (points[p_id].type) {
    int t_id = points[p_id].id;
    if (points[p_id].is_start) {
      started[t_id] = true;
    } else ended[t_id] = true;
    if (started[t_id] && ended[t_id])
      ++t_ans;    
  } // ignore for alien points
}
void remove(int p_id) {
  if (points[p_id].type) {
    int t_id = points[p_id].id;
    if (started[t_id] && ended[t_id])
      --t_ans;
    if (points[p_id].is_start) {
      started[t_id] = false;
    } else ended[t_id] = false;
  } // ignore for alien points
}
void move(int l, int r) {
  if (t_l < l) {
    for (int i = t_l; i < l; ++i)
      remove(i);
  } else if (l < t_l) {
    for (int i = t_l - 1; i >= l; --i)
      add(i);
  }
  if (t_r < r) {
    for (int i = t_r + 1; i <= r; ++i)
      add(i);
  } else if (r < t_r) {
    for (int i = t_r; i > r; --i)
      remove(i);
  }
  t_l = l, t_r = r;
}
void solveIntervals() {
  t_ans = t_l = t_r = 0;
  int l, r;
  for (int i = 1; i <= i_ptr; ++i) {
    l = intervals[i].p_s;
    r = intervals[i].p_e;
    move(l, r);
    queries[intervals[i].q_id].ans -= t_ans;
  }
}
void markRanges() {
  int l, r, i_id, val;
  l = val = 1;
  while (l <= p_ptr) {
    for (r = l; r + 1 <= p_ptr && points[l].val == points[r + 1].val; ++r);
    for (int i = l; i <= r; ++i) {
      i_id = points[i].m_id;
      if (i_id) {
        if (intervals[i_id].s == points[i].val)
          intervals[i_id].p_s = l;
        else if (intervals[i_id].e == points[i].val)
          intervals[i_id].p_e = r;
      }
      points[i].val = val;
    }
    l = r + 1;
    ++val;
  }
}
void program() {
  int s, e;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &s, &e);
    addToPoints(s, e, i, true);
    INF = max(INF, BUFF(e));
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    queries[i].ans = n;
    scanf("%d", &queries[i].k);
    for (int j = 1; j <= queries[i].k; ++j) {
      scanf("%d", &queries[i].aliens[j]);
      INF = max(INF, BUFF(queries[i].aliens[j]));
    }
  }
  generateIntervals();
  sortAllPoints();
  markRanges();
  sortIntervalsbyMosAlgorithm();
  solveIntervals();
  for (int i = 1; i <= q; ++i)
    printf("%d\n", queries[i].ans);

}
int main() {
  program();
  return 0;
}
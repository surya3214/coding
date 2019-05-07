// RTE
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define Q_MAX 5000
#define K_MAX 20
#define INTERVALS_MAX (10 * (BUFF(K_MAX) * BUFF(Q_MAX)))
#define POINTS_MAX (int) (10 * (1e5 + (INTERVALS_MAX)))
#define BLOCK_SIZE 360
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
  int id, val;
  bool type; // true if an interval; false for points
  bool is_start; // valid only if |type| is true; true for s, false for e
} points[BUFF(POINTS_MAX)];
int p_ptr;
struct I {
  int q_id, s, e;
} intervals[BUFF(INTERVALS_MAX)];
int i_ptr, block_size = BLOCK_SIZE;
void addToPoints(int s, int e, int id, bool type) {
  ++p_ptr;
  points[p_ptr].type = type;
  points[p_ptr].id = id;
  points[p_ptr].val = s;
  points[p_ptr].is_start = true;
  ++p_ptr;
  points[p_ptr].type = type;
  points[p_ptr].id = id;
  points[p_ptr].val = e;
  points[p_ptr].is_start = false;
}
void addToIntervals(int q_id, int s, int e) {
  if (s >= e)
    return;
  ++i_ptr;
  intervals[i_ptr].q_id = q_id;
  intervals[i_ptr].s = s;
  intervals[i_ptr].e = e;
  addToPoints(s, e, q_id, false);
}
void generateIntervals() {
  int l, r;
  for (int i = 1; i <= q; ++i) {
    sort(queries[i].aliens + 1, queries[i].aliens + 1 + queries[i].k);
    l = 1;
    for (int j = 1; j <= queries[i].k; ++j) {
      r = queries[i].aliens[j] - 1;
      addToIntervals(i, l, r);
      l = queries[i].aliens[j] + 1;
    }
    addToIntervals(i, l, INF);
  }
}
bool i_comparator(I a, I b) {
  int a_blk = a.s / block_size;
  int b_blk = b.s / block_size;
  if (a_blk != b_blk)
    return a_blk < b_blk;
  return a.e < b.e;
}
void sortIntervalsbyMosAlgorithm() {
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
int getMid(int l, int r) { return l + (r - l) / 2; }
int findLeftMost(int x) {
  int l, r, mid;
  l = 1, r = p_ptr;
  while (l < r) {
    mid = getMid(l, r);
    if (points[mid].val >= x)
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
void solveIntervals() {
  t_ans = t_l = t_r = 0;
  int l, r;
  for (int i = 1; i <= i_ptr; ++i) {
    l = findLeftMost(intervals[i].s);
    r = findLeftMost(intervals[i].e + 1) - 1;
    move(l, r);
    queries[i].ans -= t_ans;
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
  sortIntervalsbyMosAlgorithm();
  sortAllPoints();
  solveIntervals();
  for (int i = 1; i <= q; ++i)
    printf("%d\n", queries[i].ans);

}
int main() {
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}
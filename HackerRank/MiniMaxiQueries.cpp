//
#include <bits/stdc++.h>
#define N_MAX 50010
#define VAL_MAX 999999
using namespace std;
int n, l, r, val;
int min_ans, max_ans;
struct S {
  int first_pos, last_pos, min_dist;
  int time, last_updated;
  bool lazy, contains;
} segment_tree[N_MAX * 5];
int getMid(int l, int r) { return l + (r - l) / 2; }
int getLeftSegment(int idx) { return idx * 2; }
int getRightSegment(int idx) { return idx * 2 + 1; }
void toggleLazy(int s_idx) { segment_tree[s_idx].lazy = !segment_tree[s_idx].lazy; }
void propagateLazy(int s_idx) {
  int s_left = getLeftSegment(s_idx);
  int s_right = getRightSegment(s_idx);
  toggleLazy(s_idx);
  toggleLazy(s_left);
  toggleLazy(s_right);
}
void update(int s_start, int s_end, int s_idx, int q_start, int q_end) {
  if (s_end < q_start || q_end < s_start)
    return;
  if (s_start == s_end) {
    S *p = &segment_tree[s_idx];
    if (p->lazy) {
      p->lazy = false;
      return;
    }
    if (p->contains) // already set; undo
      p->contains = false;
    else p->contains = true, p->first_pos = p->last_pos = s_start, p->min_dist = VAL_MAX;;
    return;
  }  
  if (q_start <= s_start && s_end <= q_end) {
    toggleLazy(s_idx);
    return;
  }
  if (segment_tree[s_idx].lazy)
    propagateLazy(s_idx);
  segment_tree[s_idx].time++;
  int s_mid = getMid(s_start, s_end);
  int s_left = getLeftSegment(s_idx);
  int s_right = getRightSegment(s_idx);
  update(s_start, s_mid, s_left, q_start, q_end);
  update(s_mid + 1, s_end, s_right, q_start, q_end);
}
struct S *getSegment(int s_start, int s_end, int s_idx, int q_start, int q_end) {
  struct S *t = new struct S;
  if (q_end < s_start || s_end < q_start) {
    t->contains = false;
    return t;
  }
  struct S *p = &segment_tree[s_idx];
  struct S *left_child, *right_child;
  if (s_start == s_end) {
    if (p->lazy) {
      p->lazy = false;
      if (p->contains)
        p->contains = false;
      else p->contains = true;
    }
    if (p->contains) {
      t->contains = true;
      t->first_pos = t->last_pos = s_start;
      t->min_dist = VAL_MAX;
    } else t->contains = false;
    return t;
  }
  if (p->time != 0 && p->time == p->last_updated) {
    // already computed
    t->contains = p->contains;
    if (p->contains) {
      t->first_pos = p->first_pos;
      t->last_pos = p->last_pos;
      t->min_dist = p->min_dist;
    }
    return t;
  }
  if (segment_tree[s_idx].lazy)
    propagateLazy(s_idx);
  int s_mid = getMid(s_start, s_end);
  int s_left = getLeftSegment(s_idx);
  int s_right = getRightSegment(s_idx);
  left_child = getSegment(s_start, s_mid, s_left, q_start, q_end);
  right_child = getSegment(s_mid + 1, s_end, s_right, q_start, q_end);
  // prepare t from the two segments
  t->contains = false;
  t->min_dist = VAL_MAX;
  t->first_pos = N_MAX;
  t->last_pos = 0;
  if (left_child->contains) {
    t->contains = true;
    t->first_pos = min(t->first_pos, left_child->first_pos);
    t->last_pos = max(t->last_pos, left_child->last_pos);
    t->min_dist = min(t->min_dist, left_child->min_dist);
  }
  if (right_child->contains) {
    t->contains = true;
    t->first_pos = min(t->first_pos, right_child->first_pos);
    t->last_pos = max(t->last_pos, right_child->last_pos);
    t->min_dist = min(t->min_dist, right_child->min_dist);
  }
  if (left_child->contains && right_child->contains)
    t->min_dist = min(t->min_dist, right_child->first_pos - left_child->last_pos);
  if (t->contains) {
     min_ans = min(min_ans, t->min_dist);
     if (t->first_pos != t->last_pos)
      max_ans = max(max_ans, t->last_pos - t->first_pos);
  }
  if (q_start <= s_start && s_end <= q_end) {
    p->last_updated = p->time;
    p->contains = t->contains;
    p->first_pos = t->first_pos;
    p->last_pos = t->last_pos;
    p->min_dist = t->min_dist;
  }
  return t;
}
void program() {
  int q, type;
  S *result;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= q; i++) {
    scanf("%d", &type);
    switch(type) {
      case 1:
        scanf("%d %d %d", &l, &r, &val);
        if (val)
          update(1, n, 1, l, r);
        break;
      case 2:
        scanf("%d %d", &l, &r);
        min_ans = VAL_MAX, max_ans = -1;
        result = getSegment(1, n, 1, l, r);
        if (min_ans == VAL_MAX)
          min_ans = -1;
        printf("%d\n", min_ans);
        break;
      case 3:
        scanf("%d %d", &l, &r);
        min_ans = VAL_MAX, max_ans = -1;
        result = getSegment(1, n, 1, l, r);
        printf("%d\n", max_ans);
        break;
    }
  }
}
int main() {
  // freopen("MiniMaxiQueries_input.txt", "r", stdin);
  program();
  return 0;
}
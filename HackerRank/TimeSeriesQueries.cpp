// AC
#include <iostream>
#include <cstdio>
#define N_MAX 100010
using namespace std;
int n, q;
struct {
  int time;
  int stock_price;
} data_points[N_MAX];
int max_until[N_MAX];
int segment_tree[N_MAX * 4];
int getMid(int l, int r) {
  return l + (r - l) / 2;
}
int binarySearch(int l, int r, int key) {
  int mid;
  while (l < r) {
    mid = getMid(l, r);
    if (max_until[mid] >= key)
      r = mid;
    else l = mid + 1;
  }
  if (max_until[r] >= key)
    return r;
  return -1;
}
int getIndex(int l, int r, int time) {
  int mid;
  while (l < r) {
    mid = getMid(l, r);
    if (data_points[mid].time < time)
      l = mid + 1;
    else r = mid;
  }
  if (data_points[r].time >= time)
    return r;
  return -1;
}
int getLeftChild(int i) {
  return i * 2;
}
int getRightChild(int i) {
  return i * 2 + 1;
}
int query(int s_start, int s_end, int s_idx, int q_start, int q_end) {
  if (q_end < s_start || s_end < q_start)
    return 0;
  if (q_start <= s_start && s_end <= q_end)
    return segment_tree[s_idx];
  int left_child = getLeftChild(s_idx);
  int right_child = getRightChild(s_idx);
  int s_mid = getMid(s_start, s_end);
  return max(query(s_start, s_mid, left_child, q_start, q_end), query(s_mid + 1, s_end, right_child, q_start, q_end));
  return 0;
}
void insert(int s_start, int s_end, int s_idx, int q_id, int value) {
  if (q_id < s_start || s_end < q_id)
    return;
  if (s_start == s_end) {
    if (s_start == q_id)
      segment_tree[s_idx] = value;
    return;
  }
  int left_child = getLeftChild(s_idx);
  int right_child = getRightChild(s_idx);
  int s_mid = getMid(s_start, s_end);
  insert(s_start, s_mid, left_child, q_id, value);
  insert(s_mid + 1, s_end, right_child, q_id, value);
  segment_tree[s_idx] = max(segment_tree[left_child], segment_tree[right_child]);
}
void program() {
  int type, value, ans;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; i++)
    scanf("%d", &data_points[i].time);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &data_points[i].stock_price);
    max_until[i] = max(max_until[i - 1], data_points[i].stock_price);
    insert(1, n, 1, i, data_points[i].stock_price);
  }
  for (int i = 1; i <= q; i++) {
    scanf("%d %d", &type, &value);
    if (type == 1) {
      ans = binarySearch(1, n, value);
      if (ans == -1)
        printf("-1\n");
      else printf("%d\n", data_points[ans].time);
    } else if (type == 2) {
      int idx = getIndex(1, n, value);
      if (idx == -1)
        printf("-1\n");
      else printf("%d\n", query(1, n, 1, idx, n));
    }
  }
}
int main() {
  program();
  return 0;
}
// AC - Square Root Decomposition - Ayyyyyyyyyyyyyyyyyyyy!!!!!!!!!!!!!!!
#include <bits/stdc++.h>
#define N_MAX 100010
using namespace std;
int n, q, l, r;
int block_size, block_count;
struct P {
  int idx, h;
} People[N_MAX];
int look_up[N_MAX];
bool comparator(P a, P b) {
  return a.h < b.h;
}
int getBlockLeft(int blk_idx) { return (blk_idx - 1) * block_size + 1; }
int getBlockRight(int blk_idx) { return min(n, blk_idx * block_size); }
int getBlockIdx(int i) { return ((i - 1) / block_size) + 1; }
int getMid(int l, int r) { return l + (r - l) / 2; }
int binarySearch(int l, int r, int x) {
  int cnt = 0;
  int val, blk, l_blk;
  blk = getBlockIdx(l);
  l_blk = getBlockLeft(blk);
  while (l <= r) {
    int mid = getMid(l, r);
    val = People[mid].h;
    if (val <= x)
      l = mid + 1;
    else r = mid - 1;
  }
  if ((l - 1) >= l_blk && People[l - 1].h <= x)
    return (l - 1) - l_blk + 1;
  else return 0;
}
int findCountInSegment(int x) {
  int cnt = 0, t_r, val;
  int blk_l, blk_r, blk;
  while (l <= r) {
    blk = getBlockIdx(l);
    blk_l = getBlockLeft(blk);
    blk_r = getBlockRight(blk);
    while (l == blk_l && blk_r <= r) {
      cnt += binarySearch(blk_l, blk_r, x);
      l = blk_r + 1;
      blk = getBlockIdx(l);
      blk_l = getBlockLeft(blk);
      blk_r = getBlockRight(blk);
    }
    t_r = min(r, blk_r);
    while (l <= t_r) {
      val = People[look_up[l]].h;
      if (val <= x)
        cnt++;
      l++;
    }
  }
  return cnt;
}
void swapUtil(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}
void swap(int x, int y) {
  swapUtil(People[x].h, People[y].h);
  swapUtil(People[x].idx, People[y].idx);
  look_up[People[x].idx] = x;
  look_up[People[y].idx] = y;
}
void update(int idx, int x) {
  int t_p = look_up[idx];
  int t_b = getBlockIdx(idx);
  int t_l = getBlockLeft(t_b);
  int t_r = getBlockRight(t_b);
  People[t_p].h = x;
  if (t_p != t_l && People[t_p].h < People[t_p - 1].h) {
    while (t_p != t_l && People[t_p].h < People[t_p - 1].h) {
      swap(t_p, t_p - 1);
      t_p--;
    }
  } else if (t_p != t_r && People[t_p + 1].h < People[t_p].h) {
    while (t_p != t_r && People[t_p + 1].h < People[t_p].h) {
      swap(t_p, t_p + 1);
      t_p++;
    }
  }
}
void program() {
  int type, p, x, idx;
  scanf("%d %d", &n, &q);
  block_size = sqrt(n), block_count = getBlockIdx(n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &People[i].h);
    People[i].idx = i;
  }
  for (int blk = 1; blk <= block_count; blk++) {
    l = getBlockLeft(blk);
    r = getBlockRight(blk);
    sort(People + l, People + r + 1, comparator);
  }
  for (int i = 1; i <= n; i++)
    look_up[People[i].idx] = i;
  for (int i = 1; i <= q; i++) {
    scanf("%d", &type);
    switch(type) {
      case 1:
        scanf("%d %d", &idx, &x);
        update(idx, x);
        break;
      case 2:
        scanf("%d %d %d", &l, &r, &x);
        printf("%d\n", findCountInSegment(x));
        break;
    }
  }
}
int main() {
  program();
  return 0;
}
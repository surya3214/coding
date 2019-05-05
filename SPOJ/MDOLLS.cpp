// AC Ayyyyyyyyyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define M_MAX 20000
using namespace std;
struct S {
  int w, h;
} dolls[BUFF(M_MAX)];
int m;
struct S t_queue[2 * BUFF(M_MAX)];
int l, r;
int getMid(int l, int r) { return l + (r - l) / 2; }
bool my_comparator(struct S a, struct S b) {
  if (a.w < b.w || (a.w == b.w && a.h < b.h))
    return true;
  return false;
}
void reset() {
  l = r = M_MAX;
  t_queue[l].w = t_queue[l].h = 0;
}
int findCandidateFor(int l, int r, int h) {
  int mid;
  while (l <= r) {
    mid = getMid(l, r);
    if (t_queue[mid].h < h)
      l = mid + 1;
    else r = mid - 1;
  }
  return l - 1;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  while (tcase--) {
    reset();
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
      scanf("%d %d", &dolls[i].w, &dolls[i].h);
    sort(dolls + 1, dolls + 1 + m, my_comparator);
    int pos = 1, end, t_pos;
    int t_l, t_r;
    while (pos <= m) {
      t_l = l, t_r = r;
      end = pos;
      while (end + 1 <= m && dolls[pos].w == dolls[end + 1].w )
        end++;
      for (int i = end; i >= pos; i--) {
        if (dolls[i].h <= t_queue[l].h || dolls[i].w == t_queue[l].w) {
          l--;
          t_l = l;
          t_queue[l] = dolls[i];
        } else {
          t_pos = findCandidateFor(t_l, t_r, dolls[i].h);
          t_queue[t_pos] = dolls[i];
          t_r = t_pos - 1;
        }
      }
      pos = end + 1;
    }
    printf("%d\n", r - l + 1);
  }
}
int main() {
  program();
  return 0;
}
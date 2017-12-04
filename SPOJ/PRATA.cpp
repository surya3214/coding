// AC
#include <iostream>
#include <cstdio>
#define P_MAX 1010
#define R_MAX 9
#define COOKS_MAX 51
using namespace std;
int pratas, cooks, ranks[COOKS_MAX], min_rank;
int max_time;
int getMid(int l, int r) {
  return l + (r - l) / 2;
}
bool canBeCooked(int time) {
  int cooked_so_far = 0;
  int time_taken, cooked;
  for (int i = 0; i < cooks; i++) {
    cooked = 0;
    for (time_taken = 0; time_taken <= time; time_taken += cooked * ranks[i])
      cooked++;
    cooked_so_far += cooked - 1;
    if (cooked_so_far >= pratas)
      return true;
  }
  return false;
}
int binary_search() {
  int l, r, mid;
  l = 1;
  r = min_rank * pratas * (pratas + 1) / 2;
  while (l < r) {
    mid = getMid(l, r);
    if (canBeCooked(mid))
      r = mid;
    else l = mid + 1;
  }
  return r;
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &pratas);
    scanf("%d", &cooks);
    min_rank = R_MAX;
    for (int i = 0; i < cooks; i++) {
      scanf("%d", &ranks[i]);
      if (ranks[i] < min_rank)
        min_rank = ranks[i];
    }
    printf("%d\n", binary_search());
  }
}
int main() {
  program();
  return 0;
}
// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 18
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
ll n;
int q, k, len;
struct {
  ll max;
  ll min;
} computed[BUFF(LEN_MAX)];
struct {
  bool taken;
  int val;  
} digits[BUFF(LEN_MAX)];
void resetDigits() {
  for (int i = 1; i <= len; ++i)
    digits[i].taken = false;
}
struct {
  bool inited;
  int last_chosen_idx;
  int cur_best_idx;
  int cur_left;
  ll val;
} taken_state;
void reset() {
  resetDigits();
  taken_state.val = 0;
  taken_state.inited = false;
  taken_state.last_chosen_idx = 0;
}
void updateCurState(int idx, bool type) {
  if (!taken_state.inited) {
    taken_state.cur_best_idx = idx;
    taken_state.inited = true;
  } else {
    if (type) {
      if (digits[idx].val > digits[taken_state.cur_best_idx].val)
        taken_state.cur_best_idx = idx;
    } else {
      if (digits[idx].val < digits[taken_state.cur_best_idx].val)
        taken_state.cur_best_idx = idx;
    }
  }
}
void updateCurBest() {
  taken_state.val = taken_state.val * 10 + digits[taken_state.cur_best_idx].val;
  taken_state.last_chosen_idx = taken_state.cur_best_idx;
  taken_state.inited = false;
  digits[taken_state.cur_best_idx].taken = true;
}
void process() {
  len = 0;
  ll x = n;
  while (x) {
    x /= 10;
    ++len;
  }
  x = n;
  for (int i = len; i >= 1; --i) {
    digits[i].val = x % 10;
    x /= 10;
  }
  computed[0].min = computed[0].max = n;
  computed[len].min = computed[len].max = 0;
  for (int i = 1; i < len; ++i) { // computed[len - i]
    reset();
    taken_state.cur_left = i;
    while (taken_state.cur_left) {
      for (int j = taken_state.last_chosen_idx + 1; j <= len - taken_state.cur_left + 1; ++j) {
        if (!digits[j].taken)
          updateCurState(j, false); // false picks the minimum digit
      }
      updateCurBest();
      --taken_state.cur_left;
    }
    computed[len - i].min = taken_state.val;
    reset();
    taken_state.cur_left = i;
    while (taken_state.cur_left) {
      for (int j = taken_state.last_chosen_idx + 1; j <= len - taken_state.cur_left + 1; ++j) {
        if (!digits[j].taken)
          updateCurState(j, true); // true picks the maximum digit
      }
      updateCurBest();
      --taken_state.cur_left;
    }
    computed[len - i].max = taken_state.val;
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%lld %d", &n, &q);
    process();
    printf("Case %d:\n", t);
    for (int i = 1; i <= q; ++i) {
      scanf("%d", &k);
      printf("%lld %lld\n", computed[k].max, computed[k].min);
    }
  }
}
int main() {
  program();
  return 0;
}
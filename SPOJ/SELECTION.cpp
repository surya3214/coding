// AC Window Ayyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 2500
#define M_MAX 2500
#define BEAUTY_MAX (N_MAX * M_MAX)
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m, k, ans;
struct B {
  int value;
  int flower_type;
} beauty[BUFF(BEAUTY_MAX)];
int b_ptr;
bool b_comparator(B a, B b) { return a.value < b.value; }
void addToBeauty(int val, int type) {
  ++b_ptr;
  beauty[b_ptr].flower_type = type;
  beauty[b_ptr].value = val;
}
struct {
  int l, r;
  int flowers_count[BUFF(N_MAX)];
  int at_least_k_count;
} window;
void moveL() {
  int val = beauty[window.l].value;
  while (window.l <= b_ptr && beauty[window.l].value == val) {
    if (window.flowers_count[beauty[window.l].flower_type] == k)
      --window.at_least_k_count;
    --window.flowers_count[beauty[window.l].flower_type];
    ++window.l;
  }
}
void moveR() {
  int val = beauty[window.r + 1].value;
  while (window.r + 1 <= b_ptr && beauty[window.r + 1].value == val) {
    ++window.r;
    ++window.flowers_count[beauty[window.r].flower_type];
    if (window.flowers_count[beauty[window.r].flower_type] == k)
      ++window.at_least_k_count;
  }
}
void updateAns() {
  int x = beauty[window.r].value - beauty[window.l].value;
  ans = min(ans, x);
}
void solve() {
  window.l = 1, window.r = 0;
  ans = beauty[b_ptr].value - beauty[1].value;
  while (window.r < b_ptr) {
    moveR();
    while (window.at_least_k_count == n) {
      updateAns();
      moveL();
    }
  }
}
void program() {
  scanf("%d %d %d", &n, &m, &k);
  int x, a, b, c;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %d %d", &x, &a, &b, &c);
    addToBeauty(x, i);
    for (int j = 2; j <= m; ++j) {
      x = (1LL * a * x + b) % c;
      addToBeauty(x, i);
    }
  }
  sort(beauty + 1, beauty + 1 + b_ptr, b_comparator);
  solve();
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100
#define W_MAX 50000
#define T_MAX (W_MAX + 1000)
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, target, max_reached;
int weights[BUFF(N_MAX)];
bool reached[BUFF(T_MAX)];
struct {
  bool set;
  int val;
} ans;
void reset() {
  ans.set = false;
  for (int i = 1; i <= W_MAX; ++i)
    reached[i] = false;
  reached[0] = true;
  max_reached = 0;
}
void updateAns(int x) {
  if (x < target) return;
  if (ans.set)
    ans.val = min(ans.val, x);
  else {
    ans.val = x;
    ans.set = true;
  }
}
void process(int x) {
  for (int i = max_reached; i >= 0; --i) {
    if (reached[i] && (i + x) <= T_MAX) {
      max_reached = max(max_reached, i + x);
      reached[i + x] = true;
      updateAns(i + x);
    }
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &target);
    reset();
    for (int i = 1; i <= n; ++i)
      scanf("%d", &weights[i]);
    sort(weights + 1, weights + 1 + n);
    for (int i = 1; i <= n; ++i)
      process(weights[i]);
    printf("%d\n", ans.val - target);
  }
}
int main() {
  program();
  return 0;
}
// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 20
using namespace std;
typedef long long int ll;
ll m, ans;
int n;
int input[BUFF(N_MAX)];
void reset() { ans = 0; }
void compute(int idx, ll taken_so_far) {
  if (idx == n + 1) {
    ans = max(ans, taken_so_far);
    return;
  }
  if (input[idx] + taken_so_far <= m)
    compute(idx + 1, input[idx] + taken_so_far);
  compute(idx + 1, taken_so_far);
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &input[i]);
    compute(1, 0);
    printf("%lld\n", ans);
  }
}
int main() {
  program();
  return 0;
}
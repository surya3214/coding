// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 3 * 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int trees[BUFF(N_MAX)];
int n;
ll sum_from_right[BUFF(N_MAX)];
struct {
  bool set;
  ll min;  
} ans;
void updateAns(ll t) {
  if (!ans.set) {
    ans.min = t;
    ans.set = true;
  } else ans.min = min(ans.min, t);
}
void compute() {
  ll sum = 0;
  updateAns(sum_from_right[1]);
  for (int i = 1; i <= n; ++i) {
    updateAns(sum + sum_from_right[i + 1] - ((ll) trees[i] * (n - i)));
    sum += trees[i];
  }
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &trees[i]);
  sort(trees + 1, trees + 1 + n);
  for (int i = n; i >= 1; --i)
    sum_from_right[i] = trees[i] + sum_from_right[i + 1];
  compute();
  printf("%lld\n", ans.min);
}
int main() {
  program();
  return 0;
}
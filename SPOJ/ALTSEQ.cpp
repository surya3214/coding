// AC DP
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 5000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
int seq[BUFF(N_MAX)];
bool sign[BUFF(N_MAX)];
int dp[BUFF(N_MAX)];
int t_abs(int x) { return x > 0 ? x : -x; }
int compute() {
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i] = 1;
    for (int j = i - 1; j >= 0; -- j) {
      if (t_abs(seq[i]) > t_abs(seq[j]) && sign[i] != sign[j])
        dp[i] = max(dp[i], 1 + dp[j]);
    }
    ans = max(ans, dp[i]);
  }
  return ans;
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &seq[i]);
    if (seq[i] < 0) sign[i] = 1;
  }
  printf("%d\n", compute());
}
int main() {
  program();
  return 0;
}
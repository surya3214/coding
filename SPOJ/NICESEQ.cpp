// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define MOD 1000000007
#define N_MAX 1000
#define DIGITS_MAX 10
using namespace std;
typedef long long int ll;
ll dp[BUFF(N_MAX)];
ll seen[BUFF(DIGITS_MAX)];
void apply_mod(ll &s) {
  while (s >= MOD)
    s -= MOD;
}
void preprocess() {
  dp[1] = 9;
  for (int i = 1; i < DIGITS_MAX; ++i)
    seen[i] = 1;
  ll t_seen[BUFF(DIGITS_MAX)];
  for (int i = 2; i <= N_MAX; ++i) {
    for (int j = 0; j < DIGITS_MAX; ++j)
      t_seen[j] = 0;
    for (int j = 0; j < DIGITS_MAX; ++j) {
      switch (j) {
        case 0:
          for (int k = 0; k < DIGITS_MAX; ++k) {
            t_seen[j] += seen[k];
            t_seen[k] += t_seen[j];
          }
          break;
        case 1: break;
        case 2: t_seen[j] = seen[2]; break;
        case 3: t_seen[j] = seen[3]; break;
        case 4: t_seen[j] = seen[4] + seen[2]; t_seen[2] += t_seen[j]; break;
        case 5: t_seen[j] = seen[5]; break;
        case 6: t_seen[j] = seen[6] + seen[2] + seen[3]; t_seen[2] += t_seen[j]; t_seen[3] += t_seen[j]; break;
        case 7: t_seen[j] = seen[7]; break;
        case 8: t_seen[j] = seen[8] + seen[2] + seen[4]; t_seen[2] += t_seen[j]; t_seen[4] += t_seen[j]; break;
        case 9: t_seen[j] = seen[9] + seen[3]; t_seen[3] += t_seen[j]; break;
      }
    }
    for (int j = 0; j < DIGITS_MAX; ++j) {
      seen[j] = t_seen[j];
      dp[i] += t_seen[j];
      apply_mod(seen[j]);
      apply_mod(dp[i]);
    }
  }
}
void program() {
  int tcase, n;
  preprocess();
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d", &n);
    printf("%lld\n", dp[n]);
  }
}
int main() {
  program();
  return 0;
}
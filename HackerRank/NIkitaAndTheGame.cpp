// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 17000
using namespace std;
long sum[BUFF(N_MAX)];
int n;
int getMid(int l, int r) { return l + (r - l) / 2; }
int findBS(int l, int r, long k) {
  int m;
  while (l <= r) {
    m = getMid(l, r);
    if (sum[m] < k)
      l = m + 1;
    else r = m - 1;
  }
  if (sum[r + 1] == k)
    return r + 1;
  return -1;
}
int compute(int l, int r) {
  if (l == r) return 0;
  else if (l + 1 == r) return (sum[l] - sum[l - 1]) == (sum[r] - sum[r - 1]);
  long range_sum = sum[r] - sum[l - 1];
  if (range_sum & 1) return 0;
  int pos = findBS(l, r, sum[l - 1] + range_sum / 2);
  if (pos == -1) return 0;
  return 1 + max(compute(l, pos), compute(pos + 1, r));
}
void program() {
  int tcase;
  int t;
  scanf("%d", &tcase);
  while (tcase--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &t);
      sum[i] = sum[i - 1] + t;
    }
    printf("%d\n", compute(1, n));
  }
}
int main() {
  program();
  return 0;
}
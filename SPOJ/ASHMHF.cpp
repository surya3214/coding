// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
using namespace std;
typedef long long int ll;
int n;
int hotels[BUFF(N_MAX)];
int input[BUFF(N_MAX)];
ll prefix_sum[BUFF(N_MAX)];
struct {
  int idx;
  ll diff;
} ans;
void reset() { ans.diff = -1; }
int getMid(int l, int r) { return l + (r - l) / 2; }
int findPosition(int x) {
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (hotels[mid] == x)
      return mid;
    else if (hotels[mid] < x)
      l = mid + 1;
    else r = mid - 1;
  }
}
void program() {
  int tcase;
  ll diff;
  int idx;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &input[i]);
      hotels[i] = input[i];
    }
    sort(hotels + 1, hotels + 1 + n);
    for (int i = 1; i <= n; ++i)
      prefix_sum[i] = hotels[i] + prefix_sum[i - 1];
    for (int i = 1; i <= n; ++i) {
      idx = findPosition(input[i]);
      diff = (prefix_sum[n] - prefix_sum[idx]) - (hotels[idx] * (n - idx)) + (hotels[idx] * (idx - 1)) - prefix_sum[idx - 1];
      if (ans.diff == -1 || diff < ans.diff) ans.diff = diff, ans.idx = i;
    }
    printf("Case %d: %d\n", t, ans.idx);
  }
}
int main() {
  program();
  return 0;
}
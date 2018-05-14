// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 200000
using namespace std;
typedef long long int ll;
int n, q;
ll sum[BUFF(N_MAX)];
ll died;
int died_count;
ll order;
int getMid(int l, int r) { return l + (r - l) / 2; }
int findBS() {
  int l = died_count, r = n;
  while (l <= r) {
    int mid = getMid(l, r);
    if (sum[mid] <= died)
      l = mid + 1;
    else r = mid - 1;
  }
  return l - 1;
}
void program() {
  int strength;
  scanf("%d %d", &n, &q);
  sum[n + 1] = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &strength);
    sum[i] = sum[i - 1] + strength;
  }
  died = died_count = 0;
  for (int i = 1; i <= q; i++) {
    scanf("%lld", &order);
    died += order;
    if (died >= sum[n])
      died = died_count = 0;
    else died_count = findBS();
    printf("%d\n", n - died_count);
  }
}
int main() {
  program();
  return 0;
}
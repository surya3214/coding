//
#include <iostream>
#include <cstdio>
#define N_MAX 100010
#define VAL_MAX 1000010
using namespace std;
typedef long long ll;
int n;
int cars[N_MAX];
bool seen[VAL_MAX];
ll dp[N_MAX];
void compute(int l, int r) {
  if (r > n)
    r = n;
  ll length_so_far;
  length_so_far = 0;
  int start, end, next_car, start_car;
  start = end = l - 1;
while (start < r) {
    if (end + 1 <= r) {
      next_car = cars[end + 1];
      if (!seen[next_car]) {
        seen[next_car] = true;
        end++;
        length_so_far = end - start;
      } else {
        // next_car is already taken
        start_car = cars[start + 1];
        seen[start_car] = false;
        dp[start + 1] =  length_so_far;
        length_so_far--;
        start++;
      }
    } else {
      start_car = cars[start + 1];
      seen[start_car] = false;
      dp[start + 1] = length_so_far;
      length_so_far--;
      start++;
    }
  }
}
void computeUtil(int l, int r) {
  ll total = 0;
  ll range;
  while (l <= r) {
    range = (r - l + 1);
    total += min(range, dp[l]);
    l++;
  }
  // printf("%lld\n", total);
}
void program() {
  int q, l, r;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; i++)
    scanf("%d", &cars[i]);
  compute(1, n);
  while (q--) {
    scanf("%d %d", &l, &r);
    computeUtil(l, r);
  }
}
int main() {
  freopen("CarShow2_input.txt", "r", stdin);
  program();
  return 0;
}
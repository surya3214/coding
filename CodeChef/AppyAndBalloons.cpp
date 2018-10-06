// AC Binary Search
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
ll m;
struct {
  int a, b;
} events[BUFF(N_MAX)];
ll getMid(ll l, ll r) { return l + (r - l + 1) / (ll) 2; }
bool isPossible(ll x) {
  ll t_m = m;
  ll candies_needed;
  ll balloons_needed;
  for (int i = 1; i <= n; ++i) {
    candies_needed = 1LL * events[i].a * events[i].b;
    if (candies_needed > x) {
      balloons_needed = (candies_needed - x - 1) / (ll) events[i].b + 1;
      if (balloons_needed <= t_m)
        t_m -= balloons_needed;
      else return false;
    }
  }
  return true;
}
ll findBS() {
  ll l, r, mid;
  l = 1, r = 1e18;
  while (l <= r) {
    mid = getMid(l, r);
    if (isPossible(mid))
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
void program() {
  scanf("%d %lld", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &events[i].a);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &events[i].b);
  printf("%lld\n", findBS());
}
int main() {
  program();
  return 0;
}
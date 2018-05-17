// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define INF BUFF(1e20)
using namespace std;
typedef long long int ll;
int n;
ll w, l;
struct {
  int h, r;
} trees[BUFF(N_MAX)];
ll getMid(ll l, ll r) { return l + (r - l) / 2; }
bool solvable(ll months) {
  ll wood = 0;
  ll cur;
  for (int i = 1; i <= n; i++) {
    cur = trees[i].h + (ll) months * trees[i].r;
    if (cur >= l) wood += cur;
    if (wood >= w) return true;
  }
  return false;
}
ll solve() {
  ll l, r, mid;
  l = 0, r = INF;
  while (l <= r) {
    mid = getMid(l, r);
    if (solvable(mid))
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
void program() {
  scanf("%d %lld %lld", &n, &w, &l);
  for (int i = 1; i <= n; i++)
    scanf("%d %d", &trees[i].h, &trees[i].r);
  printf("%lld\n", solve());
}
int main() {
  program();
  return 0;
}
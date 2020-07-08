// AC #Hard, #Math, #Implementation
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
const ll MOD = 998244353;
ll n, m, ways, max_cnt;
ll nonMultiples(ll l, ll r) {
  return r - (l - 1) - (r / m - (l - 1) / m);
}
void m_mod(ll &x) {
  if (x >= MOD)
    x %= MOD;
}
ll m_pow(ll base, ll exp) {
  ll ret = 1;
  m_mod(base);
  while (exp) {
    if (exp & 1) {
      ret *= base;
      m_mod(ret);
    }
    base *= base;
    m_mod(base);
    exp >>= 1;
  }
  return ret;
}
void solve() {
  max_cnt = 0, ways = 1;
  for (ll size = 1, x = 1, l, r = n, groups, seen = 1; r; ++size, r = l - 1, seen = x) {
    if (seen <= n / m) // to cull potential overflow
      x *= m;
    else x = n + 1;
    l = (n / x) + 1;
    groups = nonMultiples(l, r);
    if (!groups)
      continue;
    max_cnt += (groups * ((size + 1) / 2));
    if (!(size & 1)) { // different choices of selection is applicable only for even count
      ways *= m_pow(size / 2 + 1, groups);
      m_mod(ways);
    }
  }
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    cin >> n >> m;
    solve();
    cout << max_cnt << " " << ways << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}

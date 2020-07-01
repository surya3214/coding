// AC #Hard, #Permutation, #Math, #Pascals, #Log
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
int w, h, l, u, r, d;
const int H_MAX = 1e5;
double logFactorial[BUFF(2 * H_MAX)];
void ready() {
  logFactorial[0] = logFactorial[1] = log(1);
  logFactorial[2] = log(2);
  for (int i = 3, r = 2 * H_MAX; i <= r; ++i)
    logFactorial[i] = logFactorial[i - 1] + log(i);
  setprecision(5);
}
double probability(int x, int y) {
  double ret =
    exp(logFactorial[x + y] - logFactorial[x] - logFactorial[y] - (x + y) * log(2));
  return ret;
}
double solve() {
  --w, --h, --l, --u, --r, --d;
  if ((l == 0 && u == 0) || (r == w && d == h) || // blocks entry or exit
      (l == 0 && r == w) || (u == 0 && d == h)) // blocks a full row or column
    return 0.0;
  double ret = 0.0;
  if (l) { // vertical strip
    for (int i = u; i <= d && i != h; ++i)
      ret += probability(i, l - 1);
    if (d == h)
      for (int i = 0; i < l; ++i)
        ret += probability(d - 1, i);
  }
  if (u) { // horizontal strip
    for (int i = l; i <= r && i != w; ++i)
      ret += probability(u - 1, i);
    if (r == w)
      for (int i = 0; i < u; ++i)
        ret += probability(i, r - 1);
  }
  return 1.0 - (ret / 2.0);
}
void program() {
  int tcase;
  double ans;
  cin >> tcase;
  for (int t = 1; t <= tcase; ++t) {
    cin >> w >> h >> l >> u >> r >> d;
    ans = solve();
    cout << "Case #" << t << ": " << ans << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  ready();
  program();
  return 0;
}
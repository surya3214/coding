// NA
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
const int N_MAX = 2e5;
int n, k;
ll ans;
vector<int> inp(BUFF(N_MAX));
void solve() {
  if (!ans)
    return;
  ll ret = 0;
  int cur_l, cur_r, cur_cnt, next_l, next_r, next_cnt;
  cur_l = cur_r = cur_cnt = 0;
  while (cur_r != n) {
    next_l = next_r = cur_r + 1;
    while (next_r + 1 <= n && inp[next_r] == inp[next_r + 1])
      ++next_r;
    next_cnt = next_r - next_l + 1;
    if (next_cnt >= k) {
      ret = 0;
      break;
    } else if (next_cnt + cur_cnt < k) {
      // no solution; collate & move on
      ret += cur_cnt * abs(inp[cur_l] - inp[next_l]);
    } else {
      // solution found
      int required = k - next_cnt;
      ret += required * abs(inp[cur_l] - inp[next_l]);
      break;
    }
    cur_l = next_l, cur_r = next_r;
    cur_cnt = cur_r - cur_l + 1;
  }
  ans = min(ans, ret);
}
void program() {
  cin >> n >> k;
  ans = LONG_MAX;
  for (int i = 1; i <= n; ++i)
    cin >> inp[i];
  sort(inp.begin() + 1, inp.begin() + 1 + n);
  solve();
  reverse(inp.begin() + 1, inp.begin() + 1 + n);
  cout << ans << endl;
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
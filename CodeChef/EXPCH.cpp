// AC DP
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e7
#define MOD (int) (1e9 + 7)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
// dp[i] - number of changes required in all substrings starting from i
ll dp[BUFF(N_MAX)];
void m_mod(ll& x) {
  if (x >= MOD)
    x %= MOD;
}
ll m_pow(ll base, int times) {
  ll ret = 1;
  for (; times; times >>= 1, base *= base, m_mod(base)) {
    if (times & 1) {
      ret *= base;
      m_mod(ret);
    }
  }
  return ret;
}
void program() {
  int tcase;
  cin >> tcase;
  string s;
  int n, next;
  ll ans;
  while (tcase--) {
    cin >> n >> s;
    stack<int> brkts;
    ans = dp[n] = 0;
    for (int i = n - 1; ~i; --i) {
      switch (s[i]) {
        case '(':
          if (!brkts.empty())
            brkts.pop();
          next = (brkts.empty()) ? n : brkts.top();
          dp[i] = dp[next];
          break;
        case ')':
          dp[i] = n - i;
          if (!brkts.empty()) {
            int tmp = brkts.top();
            brkts.pop();
            next = (brkts.empty()) ? n : brkts.top();
            brkts.push(tmp);
            dp[i] += dp[next];
          }
          brkts.push(i);
          break;
        case '*':
          dp[i] = dp[i + 1];
      }
      ans += dp[i];
      m_mod(ans);
    }
    ll den = 1LL * n * (n + 1) / 2;
    m_mod(den);
    den = m_pow(den, MOD - 2);
    ans *= den;
    m_mod(ans);
    cout << ans << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
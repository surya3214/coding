// Partial AC Combinatorial Math, Factorial
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n;
const int MOD = (1e9 + 7);
const int N_MAX = 1e5;
ll m_pow(ll base, int times) {
  ll ret = 1;
  for (; times; times /= 2, base = (base * base) % MOD)
    if (times & 1)
      ret = (ret * base) % MOD;
  return ret;
}
void program() {
  cin >> n;
  vector<ll> in(2 * n);
  ll total = 0;
  for (int i = 0; i < 2 * n; ++i) {
    cin >> in[i];
    total += in[i];
  }
  if (total % (n + 1)) {
    cout << "0";
    return;
  }
  ll sum = total / (n + 1);
  for (int i = 0; i < 2; ++i) {
    auto it = find(in.begin(), in.end(), sum);
    if (it == in.end()) {
      cout << "0";
      return;
    }
    in.erase(it);
  }
  sort(in.begin(), in.end());
  // find possibilities for a single pair
  ll ans = 1;
  for (int i = 0, j = 2 * n - 3; i < j; ++i, --j) {
    if (in[i] + in[j] != sum) {
      cout << "0";
      return;
    }
    if (in[i] != in[j])
      ans = (ans * 2) % MOD;
  }
  // find possibilities for combination of pairs
  for (int i = 1; i <= n - 1; ++i)
    ans = (ans * i) % MOD;
  for (int i = 0, j = 0; i < n - 1; i = j) {
    for (; j < n - 1 && in[j] == in[i]; ++j);
    int k = j - i;
    ll b = 1;
    for (int i = 1; i <= k; ++i)
      b = (b * i) % MOD;
    ans = (ans * m_pow(b, MOD - 2)) % MOD;
  }
  cout << ans;
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--) {
    program();
    cout << endl;
  }
  return 0;
}
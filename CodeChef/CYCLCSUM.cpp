// AC Prefix Sum, Prefix + Suffix
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (5e5)
#define INF (ll) 1e18
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n;
ll in[BUFF(N_MAX)], pfix[BUFF(N_MAX)], rpfix[BUFF(N_MAX)], best_in_pfix[BUFF(N_MAX)], best_in_rpfix[BUFF(N_MAX)];
void compute(bool type) {
  ll *pf, *bpf;
  if (type)
    pf = pfix, bpf = best_in_pfix;
  else pf = rpfix, bpf = best_in_rpfix;
  pf[0] = bpf[0] = -INF;
  ll sum, msf;
  sum = msf = 0;
  for (int i = 1; i <= n; ++i) {
    sum += in[i];
    pf[i] = max(pf[i - 1], sum);
    bpf[i] = max(bpf[i - 1], sum - msf);
    msf = min(msf, sum);
  }
}
void program() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> in[i];
  compute(true);
  reverse(in + 1, in + 1 + n);
  compute(false);
  ll ans;
  for (int i = 1; i <= n; ++i) {
    ans = max(best_in_rpfix[n - i + 1], best_in_pfix[i - 1]);
    ans = max(ans, rpfix[n - i + 1] + pfix[i - 1]);
    cout << ans << " ";
  }
  cout << endl;
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--)
    program();
  return 0;
}
// AC XOR
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n;
int a[BUFF(N_MAX)], b[BUFF(N_MAX)], ans[BUFF(N_MAX)];
void program() {
  int required = 0;
  cin >> n;
  map<int, int> mp;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    required ^= a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    required ^= b[i];
    ++mp[b[i]];
  }
  for (int i = 1, needed; i <= n; ++i) {
    needed = a[i] ^ required;
    if (!mp[needed]) {
      cout << "-1" << endl;
      return;
    }
    --mp[needed];
    ans[i] = needed;
  }
  for (int i = 1; i <= n; ++i)
    cout << ans[i] << " ";
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
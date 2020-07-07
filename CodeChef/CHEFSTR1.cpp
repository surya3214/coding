// AC #Easy
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
const int N_MAX = 1e5;
void program() {
  int tcase, n;
  int guitar[BUFF(N_MAX)];
  cin >> tcase;
  while (tcase--) {
    ll ans = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> guitar[i];
      if (i > 1)
        ans += abs(guitar[i] - guitar[i - 1]) - 1;
    }
    cout << ans << endl;
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

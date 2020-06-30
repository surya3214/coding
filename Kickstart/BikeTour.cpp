// AC #Simple
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
const int N_MAX = 100;
int points[BUFF(N_MAX)];
void program() {
  int tcase, n;
  cin >> tcase;
  for (int t = 1, ans; t <= tcase; ++t) {
    ans = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> points[i];
    for (int i = 2; i < n; ++i)
      if (points[i] > points[i - 1] && points[i] > points[i + 1])
        ++ans;
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
  program();
  return 0;
}
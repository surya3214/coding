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
const int N_MAX = 1000;
ll routes[BUFF(N_MAX)];
void program() {
  int tcase, n;
  ll d;
  cin >> tcase;
  for (int t = 1; t <= tcase; ++t) {
    cin >> n >> d;
    for (int i = 1; i <= n; ++i)
      cin >> routes[i];
    for (int i = n; i; --i)
      d = (d / routes[i]) * routes[i];
    cout << "Case #" << t << ": " << d << endl;
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
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
void program() {
  int d1, m1, y1, d2, m2, y2;
  // returned, expected
  cin >> d1 >> m1 >> y1 >> d2 >> m2 >> y2;
  int ans = 0;
  if (y1 > y2)
    ans = 10000;
  else if (y1 == y2 && m1 >= m2) {
    if (m1 == m2 && d1 > d2)
      ans = (d1 - d2) * 15;
    else ans = (m1 - m2) * 500;
  }
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

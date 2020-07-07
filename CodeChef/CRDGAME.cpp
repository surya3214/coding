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
int getRep(int x) {
  int ret = 0;
  while (x) {
    ret += (x % 10);
    x /= 10;
  }
  return ret;
}
void program() {
  int tcase, n, chef, morty;
  cin >> tcase;
  while (tcase--) {
    cin >> n;
    chef = morty = 0;
    for (int i = 1, a, b; i <= n; ++i) {
      cin >> a >> b;
      a = getRep(a), b = getRep(b);
      if (a == b)
        ++chef, ++morty;
      else if (a > b)
        ++chef;
      else ++morty;
    }
    if (chef == morty)
      cout << "2 " << chef << endl;
    else if (chef > morty)
      cout << "0 " << chef << endl;
    else cout << "1 " << morty << endl;
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

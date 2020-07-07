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
int k;
void solve() {
  cout << 'O';
  --k;
  for (int pos = 2; pos <= 64; ++pos) {
    if (k) {
      cout << '.';
      --k;
    } else cout << 'X';
    if (pos % 8 == 0)
      cout << endl;
  }
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    cin >> k;
    solve();
    cout << endl;
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

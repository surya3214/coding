// AC #Simple, #Math
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
int n, k, b1, b2;
void solve() {
  int total = 0;
  for (int i = n - 1; i; --i) {
    total += (n - i);
    if (total >= k) {
      b1 = i;
      break;
    }
  }
  b2 = b1 + 1;
  while (total != k) {
    ++b2;
    --total;
  }
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    cin >> n >> k;
    solve();
    for (int i = 1; i <= n; ++i) {
      if (i == b1 || i == b2)
        cout << 'b';
      else cout << 'a';
    }
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
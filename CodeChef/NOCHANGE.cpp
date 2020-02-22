// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e3
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int a, b, n, p;
int den[BUFF(N_MAX)];
bool isPossible() {
  a = b = 0;
  for (int i = 1; i <= n; ++i) {
    if (p % den[i])
      return a = i;
  }
  for (int i = 1, x, y; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      x = den[i], y = den[j];
      if (max(x, y) % min(x, y) != 0) {
        // this pair doesn't divide each other
        a = i, b = j;
        if (x > y)
          swap(a, b);
        return true;
      }
    }
  }
  return false;
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    cin >> n >> p;
    for (int i = 1; i <= n; ++i)
      cin >> den[i];
    if (isPossible()) {
      cout << "YES ";
      for (int i = 1; i <= n; ++i) {
        if (i == a)
          cout << ((p - den[b]) / den[a]) + 1 << " ";
        else if (i == b)
          cout << "1 ";
        else cout << "0 ";
      }
      cout << endl;
    } else cout << "NO" << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
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
int n, k;
void program() {
  int tcase, type, res;
  cin >> tcase;
  while (tcase--) {
    cin >> n >> k;
    type = -1;
    res = n - (k - 1) * 2;
    if (res > 0 && !(res & 1))
      type = 2;
    else {
      res = n - (k - 1);
      if (res > 0 && res & 1)
        type = 1;
    }
    if (type == -1)
      cout << "NO" << endl;
    else {
      cout << "YES" << endl;
      for (int i = 1; i < k; ++i)
        cout << type << " ";
      cout << res << endl;
    }
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
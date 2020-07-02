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
const int N_MAX = 5e4;
char x[BUFF(N_MAX)], a[BUFF(N_MAX)], b[BUFF(N_MAX)];
void program() {
  int tcase, n;
  cin >> tcase;
  while (tcase--) {
    cin >> n >> x;
    bool max_chosen = false;
    for (int i = 0; i < n; ++i) {
      if (max_chosen)
        a[i] = '0', b[i] = x[i];
      else if (x[i] == '2')
        a[i] = b[i] = '1';
      else if (x[i] == '0')
        a[i] = b[i] = '0';
      else {
        a[i] = '1', b[i] = '0';
        max_chosen = true;
      }
    }
    a[n] = b[n] = '\0';
    cout << a << endl << b << endl;
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
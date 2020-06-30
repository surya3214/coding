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
void program() {
  int tcase, n0, n1, n2;
  cin >> tcase;
  while (tcase--) {
    cin >> n0 >> n1 >> n2;
    if (!n1) {
      if (n0) {
        ++n0;
        while (n0--)
          cout << "0";
      } else {
        ++n2;
        while (n2--)
          cout << "1";
      }
    } else {
      // n1 is there
      while (n2--)
        cout << "1";
      cout << "10";
      --n1;
      while (n0--)
        cout << "0";
      bool type = true;
      while (n1--) {
        cout << type ? "1" : "0";
        type = !type;
      }
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
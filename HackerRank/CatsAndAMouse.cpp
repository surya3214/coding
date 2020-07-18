// NA
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
  int q, x, y, z, d1, d2;
  cin >> q;
  while (q--) {
    cin >> x >> y >> z;
    d1 = abs(z - x), d2 = abs(z - y);
    if (d1 == d2)
      cout << "Mouse C" << endl;
    else if (d1 < d2)
      cout << "Cat A" << endl;
    else cout << "Cat B" << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  program();
  return 0;
}

// AC #Simple, #Permutation
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
  int tcase, n;
  cin >> tcase;
  while (tcase--) {
    cin >> n;
    if (n < 4) {
      cout << "-1" << endl;
      continue;
    }
    int even = (n & 1) ? n - 1 : n;
    while (even != 4) {
      cout << even << " ";
      even -= 2;
    }
    cout << "2 4 ";
    int odd = 1;
    while (odd <= n) {
      cout << odd << " ";
      odd += 2;
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
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
void program() {
  int tcase, n;
  cin >> tcase;
  while (tcase--) {
    cin >> n;
    cout << (n - 1) / 2 << endl;
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
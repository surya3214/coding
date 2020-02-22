// AC Simple
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
int n;
string results;
void program() {
  cin >> n >> results;
  // cout << results << endl;
  for (int i = 0, a_rem = n, b_rem = n, a_won = 0, b_won = 0; results[i]; ++i) {
    if (i & 1) {
      b_won += (results[i] == '1');
      --b_rem;
    } else {
      a_won += (results[i] == '1');
      --a_rem;
    }
    if (b_won > (a_won + a_rem)) {
      cout << i + 1 << endl;
      return;
    } else if (a_won > (b_won + b_rem)) {
      cout << i + 1 << endl;
      return;
    }
  }
  cout << results.size() << endl;
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--)
    program();
  return 0;
}
// AC #Easy #Implementation
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
  int n;
  cin >> n;
  string moves;
  cin >> moves;
  int ans = 0;
  bool valley = false;
  for (int i = 0, lvl = 0; i < moves.size(); ++i) {
    if (moves[i] == 'U') {
      ++lvl;
    } else {
      if (!lvl)
        valley = true;
      --lvl;
    }
    if (!lvl && valley) {
      ++ans;
      valley = false;
    }
  }
  cout << ans << endl;
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

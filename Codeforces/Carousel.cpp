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
const int N_MAX = 2e5;
int n;
int types[BUFF(N_MAX)];
int getRep(int i, int size) {
  int ret = i % size;
  if (!ret)
    ret = size;
  return ret;
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    map<int, bool> cnt;
    int ans;
    bool reducable_pair = false;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> types[i];
      cnt[types[i]] = true;
      if (!reducable_pair && i != 1)
        reducable_pair = types[i] == types[i - 1];
    }
    if (!reducable_pair)
      reducable_pair = types[1] == types[n];
    if (cnt.size() == 1)
      ans = 1;
    else if (!(n & 1) || reducable_pair) // even or odd with reducable
      ans = 2;
    else ans = 3;
    cout << ans << endl;
    for (int i = 1, x; i <= n; ++i) {
      switch (ans) {
        case 1: x = 1; break;
        case 3:
          if (i == n)
            x = 3;
          else x = getRep(i, 2); break;
        case 2:
          if (n & 1) { // odd count
            if (reducable_pair) { // adjacent pair adjustment pending
              if (i == 1 || types[i] != types[i - 1])
                x = getRep(i, ans);
              else if (types[i] == types[i - 1]) {
                x = getRep(i + 1, ans);
                reducable_pair = false;
              } else if (i == n) {
                x = 1;
              }
            } else { // adjustment already happened
              x = getRep(i + 1, ans);
            }
          } else x = getRep(i, ans); // even count
          break;
      }
      cout << x << " ";
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

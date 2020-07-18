// AC #Easy
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
const int N_MAX = 100;
bool seen[BUFF(N_MAX)];
void program() {
  int n, ans = 0;
  cin >> n;
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    if (seen[x]) {
      ++ans;
      seen[x] = false;
    } else seen[x] = true;
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

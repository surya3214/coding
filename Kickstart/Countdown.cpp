// AC
#include <bits/stdc++.h>
using namespace std;
int one_diff, ans, previ;
void reset() {
  one_diff = ans = 0;
  previ = -1;
}
void program() {
  int tcase, n, k;
  cin >> tcase;
  for (int t = 1; t <= tcase; ++t) {
    reset();
    cin >> n >> k;
    --k;
    for (int i = 1, cur; i <= n; ++i, previ = cur) {
      cin >> cur;
      if (cur + 1 == previ) {
        ++one_diff;
      } else one_diff = 0;
      if (cur == 1 && one_diff >= k)
        ++ans;
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  program();
  return 0;
}
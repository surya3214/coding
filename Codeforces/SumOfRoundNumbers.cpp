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
int n;
struct N {
  int digit, zeros;
};
vector<N> ans;
void process() {
  ans.clear();
  int last, zeros;
  zeros = 0;
  while (n) {
    last = n % 10;
    if (last)
      ans.push_back({ last, zeros });
    ++zeros;
    n = n / 10;
  }
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    cin >> n;
    process();
    cout << ans.size() << endl;
    for (auto x: ans) {
      cout << x.digit;
      for (int i = 1; i <= x.zeros; ++i)
        cout << "0";
      cout << " ";
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
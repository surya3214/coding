// AC #Implementation, #Bruteforce, #TwoPointers
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
const int N_MAX = 8000;
int n, ans;
int in[BUFF(N_MAX)];
bool is_possible[BUFF(N_MAX)];
void reset() {
  memset(is_possible, 0, sizeof(is_possible));
  ans = 0;
}
void checkSum(int val) {
  int l, r, sum;
  l = r = 1, sum = in[1];
  auto updateTable = [val] (int sum) -> bool {
    is_possible[sum] = true;
    return is_possible[val];
  };
  while (l <= n) {
    while (r + 1 <= n && sum + in[r + 1] <= val) {
      ++r;
      sum += in[r];
      if (r - l + 1 >= 2 && updateTable(sum))
        return;
    }
    sum -= in[l];
    ++l;
    if (r - l + 1 >= 2 && updateTable(sum))
      return;
  }
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    reset();
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> in[i];
    for (int i = 1; i <= n; ++i) {
      if (!is_possible[in[i]])
        checkSum(in[i]);
      if (is_possible[in[i]])
        ++ans;
    }
    cout << ans << endl;
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
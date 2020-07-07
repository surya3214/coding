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
const int N_MAX = 1000;
int arr[BUFF(N_MAX)];
int n;
void solve() {
  int removed = 0;
  int next_l, next_r;
  next_r = 0;
  cout << n - removed << endl;
  while (1) {
    next_l = next_r = next_r + 1;
    while (next_r + 1 <= n && arr[next_r + 1] == arr[next_l])
      ++next_r;
    if (next_r == n)
      break;
    removed += next_r - next_l + 1;
    cout << n - removed << endl;
  }
}
void program() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> arr[i];
  sort(arr + 1, arr + 1 + n);
  solve();
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

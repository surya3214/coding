// AC #BinarySearch, #Medium
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
int n, k;
int getMid(int l, int r) { return l + (r - l) / 2; }
int getAns() {
  int l = 1, r = 2e9, mid, found;
  while (l < r) {
    mid = getMid(l, r);
    found = mid - (mid / n);
    if (found >= k)
      r = mid;
    else l = mid + 1;
  }
  return l;
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    cin >> n >> k;
    cout << getAns() << endl;
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
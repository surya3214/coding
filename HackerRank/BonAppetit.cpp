// NA
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
  int n, k, bill, charged;
  cin >> n >> k;
  bill = 0;
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    if (i != k)
      bill += x;
  }
  cin >> charged;
  bill /= 2;
  if (charged == bill)
    cout << "Bon Appetit" << endl;
  else cout << (charged - bill) << endl;
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
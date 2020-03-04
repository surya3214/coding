// AC DP, Math
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e6
#define mp make_pair
#define INF 1e18
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n;
int in[BUFF(N_MAX)];
ll terms[BUFF(N_MAX)];
ll max1, max2, d;
void program() {
  cin >> n;
  max1 = max2 = -INF;
  for (int i = 1; i <= n; ++i) {
    cin >> in[0];
    for (int j = 1; j <= in[0]; ++j) {
      cin >> in[j];
      if (i == 1)
        terms[j] = 0;
    }
    if (i != 1) {
      // consume max1, max2 from the previous cycle
      for (int j = 1; j <= in[0]; ++j) {
        d = 1LL * in[j] * (i - 1);
        terms[j] = max(max1 - d, max2 + d);
      }
    }
    if (i == n)
      break;
    // calculate max1, max2 for the next cycle
    max1 = max2 = -INF;
    for (int j = 1; j <= in[0]; ++j) {
      max1 = max(max1, terms[j] + (1LL * (j == 1 ? in[in[0]] : in[j - 1]) * i));
      max2 = max(max2, terms[j] - (1LL * (j == 1 ? in[in[0]] : in[j - 1]) * i));
    }
  }
  max1 = -INF;
  for (int j = 1; j <= in[0]; ++j)
    max1 = max(max1, terms[j]);
  cout << max1 << endl;
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
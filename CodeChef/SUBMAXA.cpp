// AC Linear Coefficients, Prefix sum
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e6
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<int, bool> pib;
typedef pair<string, int> psi;
int n, next_l[BUFF(2 * N_MAX)], next_r[BUFF(2 * N_MAX)];
int candies[BUFF(2 * N_MAX)];
ll c0[BUFF(N_MAX)], c1[BUFF(N_MAX)];
void reset() {
  memset(c0, 0, sizeof(c0));
  memset(c1, 0, sizeof(c1));
}
void calculateRanges() {
  // find closest left element so candies[i] < candies[next]
  for (int i = 1; i <= 2 * n; ++i) {
    next_l[i] = i - 1;
    while (next_l[i] && candies[next_l[i]] <= candies[i])
      next_l[i] = next_l[next_l[i]];
  }
  // find closest right element so candies[i] <= candies[next]
  for (int i = 2 * n; i; --i) {
    next_r[i] = i + 1;
    while (next_r[i] <= 2 * n && candies[next_r[i]] < candies[i])
      next_r[i] = next_r[next_r[i]];
  }
}
void updateCoeffs(int l, int r, ll tc0, ll tc1) {
  c0[l] += tc0;
  c1[l] += tc1;
  if (r <= n) {
    c0[r + 1] -= tc0;
    c1[r + 1] -= tc1;
  }
}
void program() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> candies[i];
  memcpy(candies + n + 1, candies + 1, (n * sizeof(candies[0])));
  calculateRanges();
  for (int i = 1, x, y; i <= n; ++i) {
    x = min(n + i - next_l[n + i], next_r[i] - i);
    y = max(n + i - next_l[n + i], next_r[i] - i);
    y = min(n, y);
    updateCoeffs(1, x, 0, candies[i]);
    updateCoeffs(x + 1, y, 1LL * x * candies[i], 0);
    updateCoeffs(y + 1, y + x - 1, 1LL * (x + y) * candies[i], -candies[i]);
  }
  for (int i = 1; i <= n; ++i) {
    c0[i] += c0[i - 1];
    c1[i] += c1[i - 1];
    cout << (c0[i] + c1[i] * i) << " ";
  }
  cout << endl;
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--) {
    reset();
    program();
  }
  return 0;
}
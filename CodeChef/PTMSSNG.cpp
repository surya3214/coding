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
bool m_comp(pii a, pii b) {
  if (a.first == b.first)
    return a.second < b.second;
  return a.first < b.first;
}
void program() {
  int tcase, n, total;
  cin >> tcase;
  while (tcase--) {
    set<pii> m_grid;
    vector<pii> points;
    cin >> n;
    total = 4 * n - 1;
    for (int i = 1, x, y; i <= total; ++i) {
      cin >> x >> y;
      auto p = mp(x, y);
      points.push_back(p);
      m_grid.insert(p);
    }
    sort(points.begin(), points.end(), m_comp);
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

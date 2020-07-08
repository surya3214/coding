// AC #Medium, #LatticeGraph
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
const int OFFSET = 1e9 + 1;
void program() {
  int tcase, n, c;
  cin >> tcase;
  while (tcase--) {
    map<pii, vector<int>> points;
    ll moves = 0;
    cin >> n >> c;
    for (int i = 1, x, y, d, t; i <= n; ++i) {
      cin >> x >> y;
      x += OFFSET, y += OFFSET;
      d = x - y, t = x % c;
      points[mp(d, t)].push_back(x);
    }
    for (auto it = points.begin(); it != points.end(); ++it) {
      sort(it->second.begin(), it->second.end());
      int sz = it->second.size(), median;
      median = ((sz + 1) / 2) - 1;
      median = it->second[median];
      for (auto x: it->second)
        moves += abs(x - median);
    }
    moves /= c;
    cout << points.size() << " " << moves << endl;
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

// AC Simple BFS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define mp make_pair
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
vector<pii> states[2];
bool cur;
int n, m, ans;
int grid[BUFF(N_MAX)];
void reset() {
  cur = false;
  states[0].clear(), states[1].clear();
  ans = 0;
}
int getGridPos(int x, int y) {
  return (x - 1) * m + 1 + y;
}
void program() {
  reset();
  cin >> n >> m;
  for (int i = 1, x; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> x;
      grid[getGridPos(i, j)] = x;
      states[cur].push_back(mp(i, j));
    }
  }
  bool next;
  auto isPossible = [] (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
  };
  for (int len = 1, p1, p2; states[cur].size(); cur = !cur, ++len) {
    ans += states[cur].size();
    next = !cur;
    states[next].clear();
    for (auto pt: states[cur]) {
      p1 = pt.first - len, p2 = pt.first + len;
      if (isPossible(p1, pt.second) && isPossible(p2, pt.second) &&
          grid[getGridPos(p1, pt.second)] == grid[getGridPos(p2, pt.second)]) {
        p1 = pt.second - len, p2 = pt.second + len;
        if (isPossible(pt.first, p1) && isPossible(pt.first, p2) &&
            grid[getGridPos(pt.first, p1)] == grid[getGridPos(pt.first, p2)]) {
          states[next].push_back(mp(pt.first, pt.second));
        }
      }
    }
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--)
    program();
  return 0;
}
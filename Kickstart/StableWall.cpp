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
vector<string> grid;
vector<vector<string>> tmp;
int n, m;
void program() {
  int tcase;
  cin >> tcase;
  for (int t = 1; t <= tcase; ++t) {
    cin >> n >> m;
    grid = vector<string>(n);
    tmp = vector<vector<string>>(n, vector<string>(m));
    for (int i = 0; i < n; ++i)
      cin >> grid[i];
    for (int i = 0; i < m; ++i) {
      if (dfs())
    }
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
// AC #Simple, #Map
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
#define SKILLS_MAX (int) 2e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
void program() {
  int tcase, n, ans;
  cin >> tcase;
  while (tcase--) {
    ans = 0;
    cin >> n;
    unordered_map<int, int> skills;
    for (int i = 1, skill; i <= n; ++i) {
      cin >> skill;
      if (!skills[skill])
        skills[skill] = 1;
      else ++skills[skill];
    }
    int unique_cnt = skills.size(), ret;
    for (auto it = skills.begin(); it != skills.end(); ++it) {
      ret = max(min(unique_cnt - 1, it->second),
                min(unique_cnt, it->second - 1));
      ans = max(ans, ret);
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
// AC
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
int n, ans, unique_cnt;
int skills[BUFF(SKILLS_MAX)];
void reset() {
  ans = unique_cnt = 0;
  for (int i = 1; i <= SKILLS_MAX; ++i)
    skills[i] = 0;
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    reset();
    cin >> n;
    for (int i = 1, skill; i <= n; ++i) {
      cin >> skill;
      if (!skills[skill])
        ++unique_cnt;
      ++skills[skill];
    }
    for (int i = 1, ret; i <= SKILLS_MAX; ++i) {
      if (skills[i]) {
        ret = max(min(unique_cnt - 1, skills[i]),
                  min(unique_cnt, skills[i] - 1));
        ans = max(ans, ret);
      }
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
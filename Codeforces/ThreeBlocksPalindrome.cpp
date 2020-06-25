// AC Adhoc, Palindrome
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define POS_MAX (int) 2e5
#define TYPE_MAX 200
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int presence_cnt[BUFF(TYPE_MAX)][BUFF(POS_MAX)];
int ans;
void reset() { ans = 0; }
void program() {
  int tcase, n;
  int vx_idx, vy_idx, px_idx, py_idx, more_len, ret, len;
  cin >> tcase;
  while (tcase--) {
    reset();
    cin >> n;
    unordered_map<int, vector<int>> positions;
    for (int i = 1, val; i <= n; ++i) {
      cin >> val;
      positions[val].push_back(i);
      for (int type = 1; type <= TYPE_MAX; ++type) {
        presence_cnt[type][i] = presence_cnt[type][i - 1];
        if (type == val)
          ++presence_cnt[type][i];
      }
    }
    for (auto it = positions.begin(); it != positions.end(); ++it) {
      for (len = 0, vx_idx = 1, vy_idx = it->second.size();
           vx_idx <= vy_idx; ++vx_idx, --vy_idx) {
        len += (vx_idx == vy_idx) ? 1 : 2;
        ans = max(ans, len);
        px_idx = it->second[vx_idx - 1] + 1;
        py_idx = it->second[vy_idx - 1] - 1;
        more_len = (px_idx <= py_idx) ? py_idx - px_idx + 1 : 0;
        if (!more_len || len + more_len <= ans)
          break;
        for (int val = 1; val <= TYPE_MAX; ++val) {
          ret = presence_cnt[val][py_idx] - presence_cnt[val][px_idx - 1];
          ans = max(ans, len + ret);
        }
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
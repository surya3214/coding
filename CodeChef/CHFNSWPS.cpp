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
int n;
ll ans;
struct S {
  int a_cnt, b_cnt;
};
map<int, S> inp;
typedef map<int, S>::iterator m_it;
void reset() {
  ans = -1;
  inp.clear();
}
void commute(m_it &it, bool dir = true) {
  if (it->second.a_cnt == it->second.b_cnt) {
    if (dir)
      ++it;
    else --it;
  }
}
void solve() {
  m_it start, end;
  start = inp.begin(), end = --inp.end();
  ll ret = 0;
  while (start != end) {
    commute(start);
    commute(end, false);
    if ((*start->second.a_cnt + *start->second.b_cnt) & 1 ||
        (*end->second.a_cnt + *end->second.b_cnt) & 1)
      return;
    if (*start->second.a_cnt)
  }
  if (*start->second.a_cnt == *start->second.b_cnt)
    ans = ret;
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    reset();
    cin >> n;
    for (int i = 1, a; i <= n; ++i) {
      cin >> a;
      if (!inp.count(a))
        inp[a] = S();
      ++inp[a].a_cnt;
    }
    for (int i = 1, b; i <= n; ++i) {
      cin >> b;
      if (!inp.count(b))
        inp[b] = S();
      ++inp[b].b_cnt;
    }
    solve();
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

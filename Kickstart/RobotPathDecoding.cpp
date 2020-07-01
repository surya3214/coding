// AC #Stack, #Easy
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
struct N {
  ll x, y, multiplier;
} ans;
const int N_MAX = 2000;
const int LIMIT = 1e9;
char moves[BUFF(N_MAX)];
void m_mod(ll &l) {
  if (l > LIMIT)
    l %= LIMIT;
  else if (l <= 0) {
    while (l <= 0)
      l += LIMIT;
  } 
}
void solve() {
  stack<N> s;
  s.push({ 1, 1, 0 });
  for (int i = 0; moves[i]; ++i) {
    if (moves[i] >= '2' && moves[i] <= '9') {
      s.push({ 0, 0, moves[i] - '0' });
      ++i;
    } else if (moves[i] == ')') {
      auto t = s.top();
      s.pop();
      s.top().x += (t.x * t.multiplier);
      s.top().y += (t.y * t.multiplier);
    } else {
      switch (moves[i]) {
        case 'N' : --s.top().x; break;
        case 'S' : ++s.top().x; break;
        case 'E' : ++s.top().y; break;
        case 'W' : --s.top().y; break;
      }
    }
    m_mod(s.top().x);
    m_mod(s.top().y);
  }
  ans.x = s.top().x;
  ans.y = s.top().y;
}
void program() {
  int tcase;
  cin >> tcase;
  for (int t = 1; t <= tcase; ++t) {
    cin >> moves;
    solve();
    cout << "Case #" << t << ": " << ans.y << " " << ans.x << endl;
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
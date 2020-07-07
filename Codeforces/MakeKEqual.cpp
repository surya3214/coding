// AC #Hard, #Implementation
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
const int N_MAX = 2e5;
int n, k;
ll ans;
int inp[BUFF(N_MAX)];
struct S {
  int val, cnt;
  ll cost;
};
vector<S> mod_inp, left_surf, right_surf;
void solve() {
  sort(inp + 1, inp + 1 + n);
  for (int i = 1; i <= n; ++i) {
    if (!mod_inp.size() || mod_inp.back().val != inp[i])
      mod_inp.push_back({ inp[i], 0, 0 });
    ++mod_inp.back().cnt;
    if (mod_inp.back().cnt == k) {
      ans = 0;
      return;
    }
  }
  ll t_cost;
  for (int i = 0, t_cnt; i < mod_inp.size(); ++i) {
    t_cnt = mod_inp[i].cnt;
    t_cost = 0;
    if (left_surf.size()) {
      auto prv = left_surf.back();
      t_cnt += prv.cnt;
      t_cost = prv.cost + 1LL * prv.cnt * abs(mod_inp[i].val - prv.val);
    }
    left_surf.push_back({ mod_inp[i].val, t_cnt, t_cost });
  }
  for (int i = mod_inp.size() - 1, t_cnt; i >= 0; --i) {
    t_cnt = mod_inp[i].cnt;
    t_cost = 0;
    if (right_surf.size()) {
      auto prv = right_surf.back();
      t_cnt += prv.cnt;
      t_cost = prv.cost + 1LL * prv.cnt * abs(mod_inp[i].val - prv.val);
    }
    right_surf.push_back({ mod_inp[i].val, t_cnt, t_cost });
  }
  reverse(right_surf.begin(), right_surf.end());
  S lft, rght;
  ll s_l_cost, s_r_cost, a, b;
  for (int i = 0, t_left, t_right, req; i < mod_inp.size(); ++i) {
    if (i == 0)
      lft = { 0, 0, 0 };
    else lft = left_surf[i - 1];
    if (i == (mod_inp.size() - 1))
      rght = { 0, 0, 0 };
    else rght = right_surf[i + 1];
    s_l_cost = lft.cost + (1LL * lft.cnt * abs(mod_inp[i].val - 1 - lft.val));
    s_r_cost = rght.cost + (1LL * rght.cnt * abs(mod_inp[i].val + 1 - rght.val));
    // give preference to left
    req = k - mod_inp[i].cnt;
    t_left = min(req, lft.cnt);
    req -= t_left;
    t_right = req;
    a = t_left ? (s_l_cost + t_left) : 0;
    b = t_right ? (s_r_cost + t_right) : 0;
    ans = min(ans, a + b);
    // give preference to right
    req = k - mod_inp[i].cnt;
    t_right = min(req, rght.cnt);
    req -= t_right;
    t_left = req;
    a = t_left ? (s_l_cost + t_left) : 0;
    b = t_right ? (s_r_cost + t_right) : 0;
    ans = min(ans, a + b);
  }
}
void program() {
  cin >> n >> k;
  ans = LONG_LONG_MAX;
  for (int i = 1; i <= n; ++i)
    cin >> inp[i];
  solve();
  cout << ans << endl;
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
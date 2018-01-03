//
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define N_MAX 200010
#define A_MAX 1000010
using namespace std;
typedef long long ll;
ll n, t, s;
ll numbers[N_MAX];
ll counts[A_MAX];
ll ans[N_MAX];
ll t_ans; 
ll t_l, t_r;
struct Q {
  ll l, r, idx;
} Query[N_MAX];
bool comparator(Q a, Q b) {
  ll a_blk = a.l / 50;
  ll b_blk = b.l / 50;
  if (a_blk != b_blk)
    return a_blk < b_blk;
  return a.r <= b.r;
}
ll formula(ll val, char type) {
  if (type == 'A')
    return (ll) val * (1 + 2 * counts[val]);
  else return (ll) val * (1 - 2 * counts[val]);
}
void computeUtil(ll l, ll r) {
  // move t_l to l
  if (t_l < l) {
    for (ll i = t_l; i < l; i++) {
      t_ans += formula(numbers[i], 'S');
      counts[numbers[i]]--;
    }
  }
  if (l < t_l) {
    for (ll i = t_l - 1; i >= l; i--) {
      t_ans += formula(numbers[i], 'A');
      counts[numbers[i]]++;
    }
  }
  // move t_r to r
  if (t_r < r) {
    for (ll i = t_r + 1; i <= r; i++) {
      t_ans += formula(numbers[i], 'A');
      counts[numbers[i]]++;
    }
  }
  if (r < t_r) {
    for (ll i = t_r; i > r; i--) {
      t_ans += formula(numbers[i], 'S');
      counts[numbers[i]]--;
    }
  }
  t_l = l, t_r = r;
}
void compute() {
  t_l = t_r = t_ans = 0;
  for (ll i = 1; i <= t; i++) {
    computeUtil(Query[i].l, Query[i].r);
    ans[Query[i].idx] = t_ans;
  }
}
void program() {
  // scanf("%I64d %I64d", &n, &t);
  cin >> n >> t;
  s = sqrt(n);
  for (ll i = 1; i <= n; i++)
    scanf("%I64d", &numbers[i]);
  for (ll i = 1; i <= t; i++) {
    // scanf("%I64d %I64d", &Query[i].l, &Query[i].r);
    cin >> Query[i].l >> Query[i].r;
    Query[i].idx = i;
  }
  sort(Query + 1, Query + 1 + t, comparator);
  compute();
  for (ll i = 1; i <= t; i++)
    cout << ans[i] << endl;
    // printf("%I64d\n", ans[i]);
}
int main() {
  program();
  return 0;
}
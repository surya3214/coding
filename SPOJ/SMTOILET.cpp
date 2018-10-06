// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 500
#define LEN_MAX 100
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
ll m;
int odor[BUFF(N_MAX)];
ll odor_sum[BUFF(N_MAX)];
char cubicles[BUFF(LEN_MAX)];
int closest_left[BUFF(LEN_MAX)];
int c_len;
struct {
  ll ans;
  ll ans_diff;
  int pos;
  ll pos_dist;
  int E;
  int total_odor;
} terms;
void reset() {
  terms.ans = terms.pos = -1;
  terms.total_odor = 0;
  for (int i = 1; i <= N_MAX; ++i)
    odor_sum[i] = 0;
}
ll t_abs(ll x) { return x >= 0 ? x : -x; }
void updateAns(int x, ll time) {
  if (terms.ans == -1)
    terms.ans = time, terms.ans_diff = t_abs(x - m);
  else if (t_abs(x - m) <= terms.ans_diff)
    terms.ans = time, terms.ans_diff = t_abs(x - m);
}
void findAns() {
  for (int i = 1; i <= n; ++i)
    updateAns(odor_sum[i], i);
  ll t_time = (t_abs(odor_sum[n] - m - 1) / terms.total_odor);
  ll t_x = odor_sum[n] + (t_time * terms.total_odor);
  updateAns(t_x, n + t_time);
}
void findE() {
  ll p = ((terms.ans - 1) / 10 + 1) * 10;
  for (c_len = 0; cubicles[c_len]; ++c_len);
  terms.E = (terms.ans * (c_len - 1)) / p;
  cubicles[terms.E] = 'E';
}
void updatePos(int pos, ll dist) {
  if (terms.pos == -1 || dist > terms.pos_dist ||
      (dist == terms.pos_dist && t_abs(terms.E - terms.pos) > t_abs(terms.E - pos)))
    terms.pos = pos, terms.pos_dist = dist;
}
void computeBestPos() {
  int last_seen = -1;
  for (int i = 0; cubicles[i]; ++i) {
    if (cubicles[i] == 'x')
      last_seen = i;
    closest_left[i] = last_seen;
  }
  last_seen = c_len;
  for (int i = c_len - 1; i >= 0; --i) {
    if (cubicles[i] == 'x')
      last_seen = i;
    else if (cubicles[i] == 'o')
      updatePos(i, t_abs(closest_left[i] - i) + t_abs(i - last_seen));
  }
}
void program() {
  int tcase, k;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %lld", &n, &m);
    scanf(" %s", cubicles);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &odor[i]);
      terms.total_odor += odor[i];
      k = odor[i];
      for (int j = i; j <= n; ++j, k += odor[i])
        odor_sum[j] += k;
    }
    findAns();
    findE();
    computeBestPos();
    printf("%lld %d\n", terms.ans, terms.pos + 1);
  }
}
int main() {
  program();
  return 0;
}
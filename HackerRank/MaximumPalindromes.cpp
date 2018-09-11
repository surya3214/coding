// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100000
#define ALPHA_CHARS_MAX 26
#define MOD (int) (1e9 + 7)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int fact[BUFF(LEN_MAX)];
int rfact[BUFF(LEN_MAX)];
char str[BUFF(LEN_MAX)];
int cnt[BUFF(LEN_MAX)][BUFF(ALPHA_CHARS_MAX)];
int t_freq[BUFF(ALPHA_CHARS_MAX)];
int n;
int getIndexFromChar(char x) { return x - 'a' + 1; }
int getCount(int l, int r) {
  int even_cnt, odd_cnt, x;
  even_cnt = odd_cnt = 0;
  ll ret = 1;
  for (int i = 1; i <= ALPHA_CHARS_MAX; ++i)
    t_freq[i] = cnt[r][i] - cnt[l - 1][i];
  for (int i = 1; i <= ALPHA_CHARS_MAX; ++i) {
    if (t_freq[i] & 1) ++odd_cnt;
    even_cnt += t_freq[i] / 2;
    ret = (ret * rfact[t_freq[i] / 2]) % MOD;
  }
  ret = (ret * max(1, odd_cnt)) % MOD;
  ret = (ret * fact[even_cnt]) % MOD;
  return ret;
}
void program() {
  int x;
  scanf("%s", str);
  for (n = 0; str[n]; ++n) {
    for (int i = 1; i <= ALPHA_CHARS_MAX; ++i)
      cnt[n + 1][i] = cnt[n][i];
    x = getIndexFromChar(str[n]);
    ++cnt[n + 1][x];
  }
  int q, l, r;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &l, &r);
    printf("%d\n", getCount(l, r));
  }
}
ll power(int x, int y) { // returns x^y
  if (!y)
    return 1;
  if (y & 1)
    return (1LL * x * power(x, y - 1)) % MOD;
  else {
    ll t = power(x, y / 2);
    return (t * t) % MOD;
  }
}
void ready() {
  ll ret;
  fact[0] = rfact[0] = 1;
  for (int i = 1; i <= LEN_MAX; ++i) {
    ret = (1LL * i * fact[i - 1]) % MOD;
    fact[i] = ret;
    ret = power(fact[i], MOD - 2);
    rfact[i] = ret;
  }
}
int main() {
  ready();
  program();
  return 0;
}
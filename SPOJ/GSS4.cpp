// AC BIT Finally!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define BLOCKS_MAX 317
#define BLOCKS_SIZE 500
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n;
int tcase;
int t_next[BUFF(N_MAX)];
ll BIT[BUFF(N_MAX)];
ll numbers[BUFF(N_MAX)];
void reset() {
  ++tcase;
  memset(BIT, 0, sizeof(BIT));
}
void t_swap(int &l, int &r) {
  if (l > r) {
    int tmp = l;
    l = r;
    r = tmp;
  }
}
ll queryBIT(int x) {
  ll ret = 0;
  while (x) {
    ret += BIT[x];
    x = x - (x & -x);
  }
  return ret;
}
void updateBIT(int x, ll val) {
  while (x <= n) {
    BIT[x] += val;
    x = x + (x & -x);
  }
}
int findNext(int idx) {
  if (t_next[idx] != idx)
    t_next[idx] = findNext(t_next[idx]);
  return t_next[idx];
}
void update(int l, int r) {
  l = findNext(l);
  ll x;
  while (l <= r) {
    if (numbers[l] != 1) {
      x = -numbers[l];
      numbers[l] = sqrt(numbers[l]);
      x += numbers[l];
      updateBIT(l, x);
      if (numbers[l] == 1)
        t_next[l] = l + 1;
    }
    l = findNext(l + 1);
  }
}
void program() {
  int q, type, l, r;
  while (scanf("%d", &n) != EOF) {
    reset();
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", &numbers[i]);
      updateBIT(i, numbers[i]);
      t_next[i] = i;
    }
    t_next[n + 1] = n + 1;
    scanf("%d", &q);
    printf("Case #%d:\n", tcase);
    for (int i = 1; i <= q; ++i) {
      scanf("%d %d %d", &type, &l, &r);
      t_swap(l, r);
      if (type) printf("%lld\n", queryBIT(r) - queryBIT(l - 1));
      else update(l, r);
    }
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}
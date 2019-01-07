// AC Permutation
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e7
#define LEN_MAX 7
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
bool is_not_prime[BUFF(N_MAX)];
int visited[BUFF(N_MAX)];
char roll_no[BUFF(LEN_MAX)];
int r_len;
int ans;
int t_time;
void reset() {
  ++t_time;
  ans = 0;
}
void compute(int bitmap, int val_formed) {
  if (!is_not_prime[val_formed] && visited[val_formed] != t_time) {
    ++ans;
    visited[val_formed] = t_time;
  }
  if (__builtin_popcount(bitmap) == r_len)
    return;
  for (int i = 0; roll_no[i]; ++i) {
    if (!((1 << i) & bitmap))
      compute(bitmap | (1 << i), (val_formed * 10) + roll_no[i] - '0');
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%s", roll_no);
    for (r_len = 0; roll_no[r_len]; ++r_len);
    compute(0, 0);
    printf("%d\n", ans);
  }
}
void init() {
  is_not_prime[0] = is_not_prime[1] = true;
  for (int i = 2; i <= N_MAX; ++i) {
    if (!is_not_prime[i]) {
      for (int j = 2; 1LL * j * i <= N_MAX; ++j)
        is_not_prime[(i * j)] = true;
    }
  }
}
int main() {
  init();
  program();
  return 0;
}
// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX (int) 1e5
#define K_MAX 100
using namespace std;
char s[BUFF(LEN_MAX)];
char w[BUFF(LEN_MAX)];
int a, b, k, s_len, w_len;
int ans;
void compute(int i, int j, int k_left) { // s[0..i - 1] && w[0..j - 1] match at this point
  if (k_left < 0 || (ans <= (k - k_left))) return;
  if (i == s_len) {
    if (j == w_len)
      ans = min(ans, k - k_left);
    else {
      k_left -= (w_len - j) * a;
      if (k_left >= 0) ans = min(ans, k - k_left);
    }
    return;
  } else if (j == w_len) compute(s_len, j, k_left - (s_len - i) * a);
  else if (s[i] == w[j]) compute(i + 1, j + 1, k_left);
  else { // make an operation
    compute(i, j + 1, k_left - a); // addition
    compute(i + 1, j, k_left - a); // deletion
    compute(i + 1, j + 1, k_left - min(2 * a, b)); // replacement
  }
}
void reset() { ans = BUFF(K_MAX); }
void program() {
  int tcase;
  scanf("%d", &tcase);
  while (tcase--) {
    reset();
    scanf(" %s %s", s, w);
    scanf("%d %d %d", &a, &b, &k);
    s_len = strlen(s), w_len = strlen(w);
    compute(0, 0, k);
    ans = (ans == (BUFF(K_MAX))) ? -1 : ans;
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
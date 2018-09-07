// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX (int) (1e5 + 5)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int ans, len;
char str[BUFF(LEN_MAX)];
void reset() {
  ans = -1;
}
void compute(int l, int r, bool move_taken, int pos_taken) {
  if (ans != -1) return;
  if (l >= r) {
    ans = pos_taken;
    return;
  }
  if (str[l] == str[r])
    compute(l + 1, r - 1, move_taken, pos_taken);
  else if (!move_taken) {
    compute(l + 1, r, true, l);
    compute(l, r - 1, true, r);
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%s", str);
    for (len = 0; str[len]; ++len);
    compute(0, len - 1, false, -1);
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
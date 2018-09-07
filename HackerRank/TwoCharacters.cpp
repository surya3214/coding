// AC DFS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 1000
#define ALPHA_CHARS_MAX 26
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, ans;
char str[BUFF(LEN_MAX)];
bool disabled[BUFF(ALPHA_CHARS_MAX)];
int getIndexFromChar(char x) { return x - 'a' + 1; }
void compute(int idx, char a, char b, int len_so_far) {
  if (!str[idx]) {
    if (len_so_far >= 2)
      ans = max(ans, len_so_far);
    return;
  }
  int x = getIndexFromChar(str[idx]);
  if (!disabled[x]) {
    if (!b) { // only a is chosen
      if (a != str[idx])
        compute(idx + 1, a, str[idx], len_so_far + 1);
      disabled[x] = true;
      compute(idx + 1, a, b, len_so_far);
      disabled[x] = false;
    } else { // a & b have been chosen already
      if (str[idx] != a && str[idx] != b) {
        disabled[x] = true;
        compute(idx + 1, a, b, len_so_far);
        disabled[x] = false;
      } else {
        bool is_odd = (len_so_far + 1) % 2;
        if (is_odd && str[idx] == a) // odd position
          compute(idx + 1, a, b, len_so_far + 1);
        else if (!is_odd && str[idx] == b)
          compute(idx + 1, a, b, len_so_far + 1);
      }
    }
  } else compute(idx + 1, a, b, len_so_far);
}
void program() {
  int x;
  scanf("%d", &n);
  scanf("%s", str);
  for (int i = 0; str[i]; ++i) {
    x = getIndexFromChar(str[i]);
    if (!disabled[x]) {
      compute(i + 1, str[i], 0, 1);
      disabled[x] = true;
    }
  }
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}
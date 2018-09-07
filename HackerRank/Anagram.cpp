// AC Strings
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 10000
#define ALPHA_CHARS_MAX 26
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int s_len, cnt;
char str[BUFF(LEN_MAX)];
int frequency[2][BUFF(ALPHA_CHARS_MAX)];
void reset() {
  cnt = 0;
  for (int i = 0; i <= ALPHA_CHARS_MAX; ++i)
    frequency[0][i] = frequency[1][i] = 0;
}
int getIndexFromChar(char x) { return x - 'a' + 1; }
void program() {
  int q, x, t_r;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%s", str);
    for (s_len = 0; str[s_len]; ++s_len);
    if (s_len % 2)
      printf("-1\n");
    else {
      reset();
      t_r = (s_len / 2) - 1;
      for (int i = 0; i <= t_r; ++i) {
        x = getIndexFromChar(str[i]);
        ++frequency[0][x];
      }
      for (int i = t_r + 1; str[i]; ++i) {
        x = getIndexFromChar(str[i]);
        ++frequency[1][x];
      }
      for (int i = 1; i <= ALPHA_CHARS_MAX; ++i)
        cnt += min(frequency[0][i], frequency[1][i]);
      printf("%d\n", t_r + 1 - cnt);
    }
  }
}
int main() {
  program();
  return 0;
}
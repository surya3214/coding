// AC Strings
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define ALPHA_CHARS_MAX 26
#define LEN_MAX 10000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char s1[BUFF(LEN_MAX)], s2[BUFF(LEN_MAX)];
int s1_len, s2_len;
int frequency[2][BUFF(ALPHA_CHARS_MAX)];
int getIndexFromChar(char x) { return x - 'a' + 1; }
void program() {
  int x;
  scanf("%s %s", s1, s2);
  for (s1_len = 0; s1[s1_len]; ++s1_len) {
    x = getIndexFromChar(s1[s1_len]);
    ++frequency[0][x];
  }
  for (s2_len = 0; s2[s2_len]; ++s2_len) {
    x = getIndexFromChar(s2[s2_len]);
    ++frequency[1][x];
  }
  int common_cnt = 0;
  for (int i = 1; i <= ALPHA_CHARS_MAX; ++i)
    common_cnt += min(frequency[0][i], frequency[1][i]);
  printf("%d", s1_len + s2_len - (2 * common_cnt));
}
int main() {
  program();
  return 0;
}
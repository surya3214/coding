// AC LCS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define ALPHA_CHARS_MAX 26
#define LEN_MAX 5000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char s1[BUFF(LEN_MAX)], s2[BUFF(LEN_MAX)];
int s1_len, s2_len;
int getIndexFromChar(char x) { return x - 'A' + 1; }
int lcs[BUFF(LEN_MAX)][BUFF(LEN_MAX)];
void compute() {
  for (int i = 0; i <= s1_len; ++i) {
    for (int j = 0; j <= s2_len; ++j) {
      if (i == 0 || j == 0)
        lcs[i][j] = 0;
      else if (s1[i - 1] == s2[j - 1])
        lcs[i][j] = 1 + lcs[i - 1][j - 1];
      else lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
    }
  }
}
void program() {
  int cnt;
  scanf("%s %s", s1, s2);
  for (s1_len = 0; s1[s1_len]; ++s1_len);
  for (s2_len = 0; s2[s2_len]; ++s2_len);
  compute();
  printf("%d\n", lcs[s1_len][s2_len]);
}
int main() {
  program();
  return 0;
}
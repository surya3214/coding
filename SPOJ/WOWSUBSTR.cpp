// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 500000
#define ALPHA_CHARS_MAX 26
#define MOD 100007
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
int cnt;
int precomputed[BUFF(ALPHA_CHARS_MAX)];
bool taken[BUFF(ALPHA_CHARS_MAX)];
void t_mod(int &x) {
  if (x >= MOD)
    x %= MOD;
}
int getIndexFromChar(char x) {
  return x - 'a' + 1;
}
void program() {
  int tcase, i, j, next;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%s", str);
    cnt = i = 0;
    j = -1;
    while (str[i] != '\0') {
      while (str[j + 1] != '\0') {
        next = getIndexFromChar(str[j + 1]);
        if (taken[next]) break;
        taken[next] = true;
        ++j;
      }
      next = getIndexFromChar(str[i]);
      taken[next] = false;
      cnt += precomputed[j - i + 1];
      t_mod(cnt);
      ++i;
    }
    printf("Case %d: %d\n", t, cnt);
  }
}
void ready() {
  for (int i = 1; i <= ALPHA_CHARS_MAX; ++i)
    precomputed[i] = (i * (i + 1)) / 2;
}
int main() {
  ready();
  program();
  return 0;
}
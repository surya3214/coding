// AC Strings
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100
#define ALPHA_CHARS_MAX 26
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
int ans;
struct {
  int time;
  int frequency[BUFF(ALPHA_CHARS_MAX)];
} stats[BUFF(LEN_MAX)][BUFF(LEN_MAX)];
int t_time;
void reset() { ++t_time; ans = 0; }
int getIndexFromChar(char x) { return x - 'a' + 1; }
void sanitizeState(int a, int b) {
  if (stats[a][b].time != t_time) {
    for (int k = 1; k <= ALPHA_CHARS_MAX; ++k)
      stats[a][b].frequency[k] = 0;
    stats[a][b].time = t_time;
  }
}
bool isAnagram(int a, int b, int c, int d) {
  sanitizeState(a, b);
  sanitizeState(c, d);
  for (int k = 1; k <= ALPHA_CHARS_MAX; ++k)
    if (stats[a][b].frequency[k] != stats[c][d].frequency[k])
      return false;
  return true;
}
void compute() {
  int x;
  int frequency[BUFF(ALPHA_CHARS_MAX)];
  for (int i = 0; str[i]; ++i) {
    for (int k = 1; k <= ALPHA_CHARS_MAX; ++k)
      frequency[k] = 0;
    for (int j = i; str[j]; ++j) {
      x = getIndexFromChar(str[j]);
      ++frequency[x];
      sanitizeState(i, j);
      for (int k = 1; k <= ALPHA_CHARS_MAX; ++k)
        stats[i][j].frequency[k] = frequency[k];
    }
  }
  for (int i = 0; str[i]; ++i)
    for (int j = i; str[j]; ++j)
      for (int k = i + 1; str[k]; ++k)
        for (int l = k; str[l]; ++l)
          if (isAnagram(i, j, k, l))
            ++ans;
}
void program() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    reset();
    scanf("%s", str);
    compute();
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}
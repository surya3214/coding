// AC Strings
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100000
#define ALPHA_CHARS_MAX 26
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
int frequency[BUFF(ALPHA_CHARS_MAX)];
int getIndexFromChar(char x) { return x - 'a' + 1; }
bool isValid() {
  bool deviation = false;
  int common_freq = 0, last_freq = 0;
  for (int i = 1; i <= ALPHA_CHARS_MAX; ++i) {
    if (!frequency[i])
      continue;
    if (!last_freq)
      last_freq = frequency[i];
    else {
      if (common_freq) {
        if (frequency[i] != common_freq) {
          if (!deviation)
            deviation = true;
          else return false;
        }
      } else {
        if (frequency[i] == last_freq) {
          common_freq = last_freq;
        } else if (frequency[i] - 1 == last_freq && !deviation) {
          common_freq = last_freq;
          deviation = true;
        } else if (frequency[i] == last_freq - 1 && !deviation) {
          common_freq = frequency[i];
          deviation = true;
        } else return false;
      }
    }
  }
  return true;
}
void program() {
  int x;
  scanf("%s", str);
  for (int i = 0; str[i]; ++i) {
    x = getIndexFromChar(str[i]);
    ++frequency[x];
  }
  if (isValid())
    printf("YES");
  else printf("NO");
}
int main() {
  program();
  return 0;
}
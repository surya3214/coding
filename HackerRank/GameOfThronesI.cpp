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
  bool met_odd = false;
  for (int i = 1; i <= ALPHA_CHARS_MAX; ++i) {
    if (frequency[i] % 2) {
      if (met_odd) return false;
      met_odd = true;
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
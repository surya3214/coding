// AC Ad hoc
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
string str;
bool isDelimiter(char x) {
  switch (x) {
    case '|':
    case '$':
    case ' ':
    case '*':
    case '@':
    case '.':
    case '&':
    case '\\':
    case '"':
    case '!':
    case '^':
    case ',':
    case '?':
      return true;
    default: return false;
  }
}
void process() {
  int l = 0, r;
  bool seen_pound;
  bool atleast_one = false;
  bool printed;
  while (1) {
    seen_pound = false;
    r = l;
    while (str[r] && !isDelimiter(str[r])) {
      if (str[r] == '#')
        seen_pound = true;
      ++r;
    }
    if (seen_pound) {
      printed = false;
      for (int i = l; i < r; ++i) {
        printf("%c", str[i]);
        atleast_one = true;
        printed = true;
      }
      if (printed)
        printf("\n");
    }
    if (!str[r])
      break;
    else l = r + 1;
  }
  if (!atleast_one)
    printf("No keywords.\n");
}
void program() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    getline(cin, str);
    while (str.length() == 0)
      getline(cin, str);
    process();
  }
}
int main() {
  program();
  return 0;
}
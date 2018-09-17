// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define ALPHA_CHARS_MAX 26
#define N_MAX 100000
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int freq[BUFF(ALPHA_CHARS_MAX)];
char str[BUFF(N_MAX)];
inline int getIndexFromChar(char x) { return x - 'a' + 1; }
void program() {
  int n, best, x;
  best = 0;
  scanf("%d", &n);
  scanf("%s", str);
  for (int i = 0; str[i]; ++i) {
    x = getIndexFromChar(str[i]);
    ++freq[x];
    best = max(best, freq[x]);
  }
  printf("%d\n", n - best);
}
int main() {
  program();
  return 0;
}
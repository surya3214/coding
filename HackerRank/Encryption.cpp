// AC Implementation
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 81
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
int s_len;
int getSquareRoot(int x) {
  int i = 1;
  while (i * i <= x)
    ++i;
  return --i;
}
void program() {
  scanf("%s", str);
  for (s_len = 0; str[s_len]; ++s_len);
  int row, col;
  col = row = getSquareRoot(s_len);
  if (row * col < s_len)
    ++col;
  if (row * col < s_len)
    ++row;
  assert(row * col >= s_len);
  for (int i = 0; i <= col - 1; ++i) {
    for (int j = i; j < s_len; j += col)
      printf("%c", str[j]);
    printf(" ");
  }
}
int main() {
  program();
  return 0;
}